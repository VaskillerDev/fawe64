import React, {Fragment} from "react";
import {CHUNK_LEN_IN_MAP} from "./GridViewGl";
import {PATH_TEXT_ARR_KEY} from "./PathModeInspector";
import rawPosToNormalPos from "./util/rawPosToNormalPos";
import gridPosToChunk from "./util/gridPosToChunk";
import entityIdToNumber from "./util/entityIdToNumber";
import globalPosToLocalPos from "./util/globalPosToLocalPos";

const EMPTY_NUMBER = 101;

export default class DownloadMapButton extends React.Component {
    
    constructor(props) {
        super(props);
        this.onDownloadMapClick = this.onDownloadMapClick.bind(this);
    }

    onDownloadMapClick(_) {
        const fileContent = this.mapToFile();
        const mapFile = new Blob([fileContent], {type: "plain/text"});
        
        const a = document.createElement("a");
        const url = URL.createObjectURL(mapFile);
        
        a.href = url;
        a.download = "map.txt";
        
        document.body.appendChild(a);
        a.click();
    }
    
    mapToFile() {
        let fileString = "const uint8_t PLAIN_LEVEL [8][8][64] = {\n"
        
        for(let i = 0; i < CHUNK_LEN_IN_MAP; i++) {
            fileString += `{ // ${i}\n`;
            
            for(let j = CHUNK_LEN_IN_MAP-1; j >= 0; j--) {
                fileString += "{";
                const chunk = localStorage.getItem(`${i}:${j}`);
                let chunkString= chunk === "-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1" 
                    ? "2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2" 
                    : chunk;

                chunkString = chunk.replaceAll("-1", "2");

                fileString += chunkString;
                
                fileString += "},\n";
            }

            fileString +=  i === 7 ? "}\n" : "},\n";
        }
        fileString += "};\n\n"
        
        const pathTextArr = JSON.parse(localStorage.getItem(PATH_TEXT_ARR_KEY));
        if (pathTextArr) {

            fileString += "const uint8_t LEVEL_PATH\n" +
                "[32]// количество возможных записей \n" +
                "[2 + 1 + (8 * 2)] // CHUNK_POS + ENTITY_ID + PATH_PER_STEP * 2 - id существа сколько шагов доступно для одного маршрута, где каждая пара [x,y]\n" +
                "= {\n"

            let pathCount = 0;
            for (const path of pathTextArr) {
                if (path === "") continue;
                const pathArr = path.split('->');

                fileString += "{";

                const entityIdNum = entityIdToNumber[pathArr[0]];
                const _pathArr = pathArr.splice(1, pathArr.length);
                const chunkPos = this.getChunkPosition(_pathArr[1]);

                fileString += `${chunkPos.x},${Math.abs(chunkPos.y - 7)},`
                fileString += `${entityIdNum},`

                let i = 0;
                for (const rawPos of _pathArr) {
                    const pos = rawPosToNormalPos(rawPos);
                    const localPos = globalPosToLocalPos(chunkPos, pos);

                    fileString += `${localPos.x},${localPos.y},`;
                    i += 1;
                }

                if (i <= 8) {
                    for (let ii = i; ii < 8; ii++) {
                        fileString += `${EMPTY_NUMBER},${EMPTY_NUMBER},`;
                    }
                }
                fileString += "},\n";
                pathCount += 1;
            }

            if (pathCount <= 32) {
                for (let ii = pathCount; ii < 32; ii++) {
                    fileString += `{101,101,101,101,101,101,101,101,101,101,101,101,101},\n`;
                }
            }
            fileString += "};\n";
        }
        
        let rockExist = false;
        let rockCount = 0;
        for (let gridPosX = 0; gridPosX < 64; gridPosX++) {
            for (let gridPosY = 0; gridPosY < 64; gridPosY++) {
                const mbRock = localStorage.getItem(`rock:${gridPosX}:${gridPosY}`);
                if (mbRock === null) continue;
                if (!rockExist) {
                    fileString += "const uint8_t ROCK_LEVEL [32][2 + 2] = { // CHUNK_POS + LOCAL_POS\n"
                    rockExist = true;
                }
                
                const [localPosX,localPosY] = mbRock.split(',');
                const localPos = {
                    x: Number.parseInt(localPosX),
                    y: Number.parseInt(localPosY)
                }
                
                const chunkPos = gridPosToChunk({x: gridPosX, y: gridPosY});
                
                fileString += `{${chunkPos.x},${Math.abs(chunkPos.y - 7)},${localPos.x},${localPos.y}},\n`
                rockCount+=1;
            }
        }
        
        if (rockExist) {
            if (rockCount <= 32) {
                for (let ii = rockCount; ii < 32; ii++) {
                    fileString += `{101,101,101,101},\n`;
                }
            }
            fileString += "};\n"
        }
        
        let itemExist = false;
        let itemCount = 0;
        for (let gridPosX = 0; gridPosX < 64; gridPosX++) {
            for (let gridPosY = 0; gridPosY < 64; gridPosY++) {
                const mbItem = localStorage.getItem(`item:${gridPosX}:${gridPosY}`);
                if (mbItem === null) continue
                if (!itemExist) {
                    fileString += "const uint8_t ITEM_LEVEL [32][2 + 2 + 1] = { // CHUNK_POS + LOCAL_POS + ITEM_ID \n"
                    itemExist = true;
                }

                const [localPosX,localPosY, itemIdNum] = mbItem.split(',');
                const localPos = {
                    x: Number.parseInt(localPosX),
                    y: Number.parseInt(localPosY)
                }
                const chunkPos = gridPosToChunk({x: gridPosX, y: gridPosY});
                
                fileString += `{${chunkPos.x},${Math.abs(chunkPos.y - 7)},${localPos.x},${localPos.y},${itemIdNum}},\n`
                itemCount +=1;
            }
        }
        
        if (itemExist) {
            if (itemCount <= 32) {
                for (let ii = itemCount; ii < 32; ii++) {
                    fileString += `{101,101,101,101,101},\n`;
                }
            }
            fileString += "};\n"
        }
        return fileString;
    }
    
    getChunkPosition(rawPos) { // "(0,0)"
        const normalPos = rawPosToNormalPos(rawPos);
        return gridPosToChunk(normalPos);
    }
    
    render() {
        return (
            <Fragment>
                <button id={'downloadMapButton'} onClick={this.onDownloadMapClick}>
                    <img src={"save.png"} alt={"path"} style={{width: '64px', height: '64px'}}/>
                </button>
            </Fragment>
        );
    };
}