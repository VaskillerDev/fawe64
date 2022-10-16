import {Fragment, Component} from "react";
import * as PIXI from 'pixi.js'
import {Viewport} from "pixi-viewport";
import TilePicker from "./TilePicker";
import TileFlipper from "./TileFlipper";
import PathModeToggler from "./PathModeToggler";
import DownloadMapButton from "./DownloadMapButton";
import PathModeInspector from "./PathModeInspector";
import rawPosToNormalPos from "./util/rawPosToNormalPos";
import RockBrushButton from "./RockBrushButton";
import gridPosToChunk from "./util/gridPosToChunk";
import globalPosToLocalPos from "./util/globalPosToLocalPos";
import ItemBrushButton from "./ItemBrushButton";
import ItemModeInspector from "./ItemModeInspector";

const BLOCK_SIZE = 16;
const CHUNK_SIZE = 8;
export const CHUNK_LEN_IN_MAP = 8;
const MAP_VIEW_SIZE = BLOCK_SIZE * CHUNK_SIZE * CHUNK_LEN_IN_MAP + 512;

export default class GridViewGl extends Component {
    
    app;
    currentPickedTileIndex = 0;

    currentPickedTileIsFlipH = false;
    currentPickedTileIsFlipV = false;
    currentPickedTileIsFlipD = false;

    tilesImg;
    rockImg;
    itemsImg;
    
    viewport;
    mouseCursorBlock;

    pathPoint;
    
    isBrushMode = false;
    isItemBrushMode = false;
    isRockBrushMode = false;
    rockBrushButtonDisableActivate = false;
    
    pathLineArr = [];
    itemIdNum = 0;

    createMap() {
        for (let i = 0 ; i < CHUNK_LEN_IN_MAP; i++) {
            for (let j = 0 ; j < CHUNK_LEN_IN_MAP; j++) {
                let chunk  = '';
                
                for (let jj = 0 ; jj < 64; jj++) {
                    chunk += jj === 63 ? '-1' : '-1,'
                }
                
                localStorage.setItem(`${i}:${j}`,chunk)
            }
        }
    }
    
    loadMap() {
        for (let i = 0 ; i < CHUNK_LEN_IN_MAP; i++) {
            for (let j = 0 ; j < CHUNK_LEN_IN_MAP; j++) {
                const chunk = localStorage.getItem(`${i}:${j}`);
                const chunkData = chunk.split(',')

                let offset = 0;
                for (const tile of chunkData) {
                    const tileInt = Number.parseInt(tile);
                    if (tileInt === -1) {
                        ++offset;
                        continue;
                    }
                    
                    let gridX = i * 8 + (offset % 8)
                    let gridY = Math.ceil((j * 8 + ((offset + 1) / 8)))
                    gridY = gridY > 0  ? gridY - 1 : gridY

                    this.spawnTileByCode(tileInt, gridX, gridY);
                    ++offset;
                }
                
                
            }
        }
        
        for (let gridPosX = 0 ; gridPosX < 64; gridPosX++) {
            for (let gridPosY = 0 ; gridPosY < 64; gridPosY++) {
                const mbRock = localStorage.getItem(`rock:${gridPosX}:${gridPosY}`);
                if (mbRock === null) continue;
                this.spawnRock(this.viewport, gridPosX, gridPosY);
            }
        }

        for (let gridPosX = 0 ; gridPosX < 64; gridPosX++) {
            for (let gridPosY = 0 ; gridPosY < 64; gridPosY++) {
                const mbRock = localStorage.getItem(`item:${gridPosX}:${gridPosY}`);
                if (mbRock === null) continue;
                this.spawnItem(this.viewport, gridPosX, gridPosY);
            }
        }
    }
    
    spawnTileByCode(tileInt, gridX, gridY) {
        let isFlipH;
        let isFlipV;
        let isFlipD;
        let tileId;

        isFlipH = tileInt >= 100;

        const tileDataWithoutId = Math.floor(tileInt / 10);
        
        const twoPosTIleInt = tileDataWithoutId > 10 ? tileDataWithoutId - 10 : tileDataWithoutId;
        tileId = tileInt % 10;
        
        isFlipV = twoPosTIleInt === 1;
        isFlipD = twoPosTIleInt === 2;
        
        if (twoPosTIleInt === 3) {
            isFlipD = true;
            isFlipV = true;
        }
        
        this.spawnTile(this.tilesImg, this.viewport, tileId, gridX, gridY, isFlipH, isFlipV, isFlipD, true)
    }

    handlePathModePathEditorChanged(count, text) {
        try {
            const dataArr = text.toLowerCase().split('->'); // "bat->(0;0)->(1;0)->(2;2)"

            const entityId = dataArr[0]; // 'bat'
            if (!ENTITY_LIST[entityId]) return;

            const len = dataArr.length;
            let gridPosArr = [];
            for (let i = 1; i < len; i++) {
                const rawPos = dataArr[i] // '(0;0)'
                if (rawPos === '') return;
                const pos = rawPosToNormalPos(rawPos);
                if (!pos) return;
                gridPosArr.push(pos);
            }

            this.processHandlePathModePathEditorChanged(entityId, count, gridPosArr);
        } catch (e) {}
    }

    processHandlePathModePathEditorChanged(entityId, count, gridPosArr) {
        this.pathLineArr[count] = gridPosArr;
        this.pathPoint.clear();
        
        for (const _gridPosArr of this.pathLineArr) {
            if (!_gridPosArr) continue;
            let prevGridPos = undefined;
            for (const gridPos of _gridPosArr) {

                const x = gridPos.x * BLOCK_SIZE + BLOCK_SIZE / 2;
                const y = gridPos.y * BLOCK_SIZE + BLOCK_SIZE / 2;

                if (prevGridPos) {
                    this.drawPathLineToPoint(this.pathPoint, undefined,
                        prevGridPos.x * BLOCK_SIZE + BLOCK_SIZE / 2,
                        prevGridPos.y * BLOCK_SIZE + BLOCK_SIZE / 2,
                        x,
                        y);
                }
                this.drawPathPoint(this.pathPoint, undefined, x, y);

                prevGridPos = gridPos;
            }
        }
    }

    handlePathModeTogglerChanged(isEnable) {
        this.setState({isPathInspectorEnabled: isEnable})
    }
    
    handleCurrentPickedTileIndex(index) {
        this.currentPickedTileIndex = index;

        this.isRockBrushMode = false;
        this.rockBrushButtonDisableActivate = true;
        
        this.setMouseCursorBlock(this.tilesImg,
            this.currentPickedTileIndex,
            this.currentPickedTileIsFlipH,
            this.currentPickedTileIsFlipV,
            this.currentPickedTileIsFlipD);
    }

    handlePathModeInspectorInit(pathTextArr) {
        console.log(pathTextArr);
    }

    handleItemBrushActivated(isActivate) {
        this.isRockBrushMode = false;
        this.isItemBrushMode = isActivate;
        this.setState({isItemInspectorEnabled: isActivate})
    }
    
    handleRockBrushActivated(isActivate) {
        this.isItemBrushMode = false;
        this.isRockBrushMode = isActivate;
        this.rockBrushButtonDisableActivate = false;
        this.setMouseCursorBlock(this.tilesImg,
            this.currentPickedTileIndex,
            this.currentPickedTileIsFlipH,
            this.currentPickedTileIsFlipV,
            this.currentPickedTileIsFlipD);
    }
    
    handleFlipTile(indexFlip, isFlip) {
        
        switch (indexFlip) {
            case 0: { this.currentPickedTileIsFlipH = isFlip; break; }
            case 1: { this.currentPickedTileIsFlipV = isFlip; break; }
            case 2: { this.currentPickedTileIsFlipD = isFlip; break; }
        }
        
        this.setMouseCursorBlock(this.tilesImg,
            this.currentPickedTileIndex,
            this.currentPickedTileIsFlipH,
            this.currentPickedTileIsFlipV,
            this.currentPickedTileIsFlipD);
    }

    handleItemIdChanged(itemIdNum) {
        this.itemIdNum = itemIdNum;

        this.setMouseCursorBlock(this.tilesImg, 0,
            this.currentPickedTileIsFlipH,
            this.currentPickedTileIsFlipV,
            this.currentPickedTileIsFlipD);
    }
    
    constructor(props) {
        super(props);
        
        this.handleItemIdChanged = this.handleItemIdChanged.bind(this);
        this.handleRockBrushActivated = this.handleRockBrushActivated.bind(this);
        this.handleItemBrushActivated = this.handleItemBrushActivated.bind(this);
        this.handlePathModeInspectorInit = this.handlePathModeInspectorInit.bind(this);
        this.handleCurrentPickedTileIndex = this.handleCurrentPickedTileIndex.bind(this);
        this.handlePathModeTogglerChanged = this.handlePathModeTogglerChanged.bind(this);
        this.handlePathModePathEditorChanged = this.handlePathModePathEditorChanged.bind(this);
        
        this.handleFlipTile = this.handleFlipTile.bind(this);
        
        this.state = {
            isPathInspectorEnabled: false,
            isItemInspectorEnabled: false
        }
    }
    
    componentDidMount() {
        PIXI.settings.SCALE_MODE = PIXI.SCALE_MODES.NEAREST;
        this.app = new PIXI.Application({
            width: window.innerWidth - 312,
            height: window.innerHeight - 128,
            view: document.getElementById("gridCanvas"),
            backgroundColor:  0x282c34,
            clearBeforeRender: true
        });
        
        document.getElementById("gridViewGl").appendChild(this.app.view)

        const viewport = new Viewport({
            screenWidth: MAP_VIEW_SIZE,
            screenHeight: MAP_VIEW_SIZE,
            worldWidth: MAP_VIEW_SIZE,
            worldHeight: MAP_VIEW_SIZE,
            
            interaction: this.app.renderer.plugins.interaction
        })

        this.viewport = viewport;
        
        const borderLine = new PIXI.Graphics();
        const gridLine = new PIXI.Graphics();
        const pathPoint = new PIXI.Graphics();
        this.pathPoint = pathPoint;
        
        viewport.addChild(pathPoint);
        viewport.addChild(borderLine);
        viewport.addChild(gridLine);
        
        viewport.sortableChildren = true;

        viewport.addListener("mousemove", (e)=> {
            let mousePos = viewport.toWorld(e.data.global.x, e.data.global.y)
            
            if (Number.isNaN(mousePos.x)) return
            
            let gridX = Math.ceil(mousePos.x / BLOCK_SIZE);
            let gridY = Math.ceil(mousePos.y / BLOCK_SIZE);

            gridX =  gridX > 0  ? gridX - 1 : gridX;
            gridY = gridY > 0  ? gridY - 1 : gridY
            
            this.mouseCursorBlock.position.set(BLOCK_SIZE * gridX + BLOCK_SIZE / 2, BLOCK_SIZE * gridY + BLOCK_SIZE / 2)
            this.props.handleGridPositionChanged(gridX,gridY);
            
            if (!this.isBrushMode) return;

            this.spawnTile(this.tilesImg,
                viewport,
                this.currentPickedTileIndex,
                gridX,
                gridY,
                this.currentPickedTileIsFlipH,
                this.currentPickedTileIsFlipV,
                this.currentPickedTileIsFlipD);
        });
        
        
        const canvas = document.getElementById("gridCanvas");

        canvas.addEventListener('mousedown', (e) => {
            if (e.button === 0 && !this.isRockBrushMode && !this.isItemBrushMode) {
                this.isBrushMode = true;
            }
        })

        canvas.addEventListener('mouseup', (e) => {
            if (e.button === 0 && !this.isRockBrushMode && !this.isItemBrushMode) {
                this.isBrushMode = false;
            }
        })
        
        viewport.addListener('clicked', (e)=> {
            
            let mousePos = viewport.toWorld(e.event.data.global.x, e.event.data.global.y)
            if (Number.isNaN(mousePos.x)) return
            let gridX = Math.ceil(mousePos.x / BLOCK_SIZE);
            let gridY = Math.ceil(mousePos.y / BLOCK_SIZE);

            gridX =  gridX > 0  ? gridX - 1 : gridX;
            gridY = gridY > 0  ? gridY - 1 : gridY
            
            // console.log(gridX, gridY);
            
            if (this.isRockBrushMode) {
                this.spawnRock(viewport, gridX, gridY);
                return;
            }
            
            if (this.isItemBrushMode) {
                this.spawnItem(viewport, gridX, gridY);
                return;
            }
            
            this.spawnTile(this.tilesImg,
                viewport,
                this.currentPickedTileIndex,
                gridX,
                gridY,
                this.currentPickedTileIsFlipH,
                this.currentPickedTileIsFlipV,
                this.currentPickedTileIsFlipD);
        });
        
        this.app.stage.addChild(viewport)

        viewport
            .drag({
                mouseButtons: 'middle'
            })
            .pinch()
            .wheel()
            .decelerate()

        viewport.fit()

        this.tilesImg = this.prepareAtlas();
        this.rockImg = this.prepareRockImg()[0];
        this.itemsImg = [this.preparePtnImg()[0], this.prepareBmbImg()[0], this.prepareW4Img()[0]];

        this.initMouseCursorBlock(viewport);
        this.setMouseCursorBlock(this.tilesImg, 0, 
            this.currentPickedTileIsFlipH,
            this.currentPickedTileIsFlipV,
            this.currentPickedTileIsFlipD);
        
        this.drawBorder(borderLine, viewport)
        this.drawGrid(gridLine, viewport);

        const isSavedMapExist = localStorage.getItem('0:0');
        isSavedMapExist ? this.loadMap() : this.createMap();
    }
    
    initMouseCursorBlock(viewport) {
        this.mouseCursorBlock = viewport.addChild(new PIXI.Sprite(PIXI.Texture.WHITE))
        this.mouseCursorBlock.width = this.mouseCursorBlock.height = BLOCK_SIZE
        this.mouseCursorBlock.position.set(0, 0)
        this.mouseCursorBlock.alpha = 0.45
        this.mouseCursorBlock.zIndex = 1;
    }
    
    setMouseCursorBlock(tiles, tileId, isFlipH, isFlipV, isFlipD) {
        this.mouseCursorBlock.texture = this.isRockBrushMode ? this.rockImg 
            : this.isItemBrushMode ? this.itemsImg[this.itemIdNum] 
            : this.tilesImg[tileId];
        
        this.mouseCursorBlock.scale.x = isFlipH? -1 : 1;
        this.mouseCursorBlock.scale.y = isFlipV? -1 : 1;
        this.mouseCursorBlock.anchor.x = 0.5
        this.mouseCursorBlock.anchor.y = 0.5
        this.mouseCursorBlock.rotation = isFlipD? (3. * Math.PI / 2) : 0;
    }
    
    spawnTile(tiles, viewport, tileId, gridX, gridY, isFlipH, isFlipV, isFlipD, withoutSave) {
        const sprite = viewport.addChild(new PIXI.Sprite(tiles[tileId]))
        sprite.width = sprite.height = BLOCK_SIZE
        sprite.position.set(BLOCK_SIZE * gridX, BLOCK_SIZE * gridY);
        sprite.scale.x = isFlipH? -1 : 1;
        sprite.scale.y = isFlipV? -1 : 1;
        sprite.anchor.x = 0.5
        sprite.anchor.y = 0.5
        sprite.rotation = isFlipD? (3. * Math.PI / 2) : 0;
        sprite.zIndex = -1;
        
        sprite.position.set( sprite.position.x + BLOCK_SIZE / 2,  sprite.position.y + BLOCK_SIZE / 2);
        
        if (withoutSave) return;
        
        let tileCode = isFlipH ? 100 : 0;
        tileCode = isFlipV ? tileCode + 10 : tileCode;
        tileCode = isFlipD ? tileCode + 20 : tileCode;
        tileCode += tileId;
        
        this.saveTile(gridX, gridY, tileCode);
    }
    
    spawnRock(viewport, gridX, gridY) {
        const sprite = viewport.addChild(new PIXI.Sprite(this.rockImg))

        sprite.width = sprite.height = BLOCK_SIZE
        //sprite.position.set(BLOCK_SIZE * gridX, BLOCK_SIZE * gridY);
        sprite.scale.x =  1;
        sprite.scale.y = 1;
        sprite.anchor.x = 0.5
        sprite.anchor.y = 0.5
        sprite.rotation = 0;
        sprite.zIndex = -1;

        sprite.position.set( sprite.position.x + BLOCK_SIZE / 2,  sprite.position.y + BLOCK_SIZE / 2);
        
        this.saveRock(gridX, gridY);
    }
    
    spawnItem(viewport, gridX, gridY) {
        const sprite = viewport.addChild(new PIXI.Sprite(this.itemsImg[this.itemIdNum]))
        sprite.width = sprite.height = BLOCK_SIZE
        sprite.position.set(BLOCK_SIZE * gridX, BLOCK_SIZE * gridY);
        sprite.scale.x =  1;
        sprite.scale.y = 1;
        sprite.anchor.x = 0.5
        sprite.anchor.y = 0.5
        sprite.rotation = 0;
        sprite.zIndex = -1;
        sprite.position.set( sprite.position.x + BLOCK_SIZE / 2,  sprite.position.y + BLOCK_SIZE / 2);
        
        this.saveItem(gridX, gridY);
    }
    
    saveRock(gridX, gridY) {
        const chunkPos = gridPosToChunk({x: gridX, y: gridY});
        const localPos = globalPosToLocalPos(chunkPos, {x: gridX, y: gridY});
        
        localStorage.setItem(`rock:${gridX}:${gridY}`, `${localPos.x},${localPos.y}`);
    }
    
    saveItem(gridX, gridY) {
        const chunkPos = gridPosToChunk({x: gridX, y: gridY});
        const localPos = globalPosToLocalPos(chunkPos, {x: gridX, y: gridY});
        
        localStorage.setItem(`item:${gridX}:${gridY}`, `${localPos.x},${localPos.y},${this.itemIdNum}`);
    }
    
    saveTile(gridX, gridY, tileCode) {
        const {x: chunkX, y: chunkY} = gridPosToChunk({x: gridX, y: gridY});
        
        const posX = gridX - chunkX * CHUNK_SIZE
        const posY = gridY - chunkY * CHUNK_SIZE;
        let posLine = (posX + posY * CHUNK_SIZE);
        posLine = posLine < 0 ? 0 : posLine
        
        const chunk = localStorage.getItem(`${chunkX}:${chunkY}`);
        const chunkData = chunk.split(',');
        
        let newChunk = '';
        let i = 0;
        for (const tile of chunkData) {
            if (i === posLine) {
                const char = i === 63? `${tileCode}` : `${tileCode},`;
                newChunk += char
                i++;
                continue;
            }
            
            newChunk += i === 63? tile : `${tile},`;
            i++;
        }
        
        localStorage.setItem(`${chunkX}:${chunkY}`, newChunk);
    }
    
    prepareAtlas() {
        const bT = PIXI.BaseTexture.from('tiles.png');
        
        return [
            new PIXI.Texture(bT, new PIXI.Rectangle(0,0, 16,16)),
            new PIXI.Texture(bT, new PIXI.Rectangle(16,0, 16,16)),
            new PIXI.Texture(bT, new PIXI.Rectangle(32,0, 16,16)),
            new PIXI.Texture(bT, new PIXI.Rectangle(48,0, 16,16)),

            new PIXI.Texture(bT, new PIXI.Rectangle(0,16, 16,16)),
            new PIXI.Texture(bT, new PIXI.Rectangle(16,16, 16,16)),
            new PIXI.Texture(bT, new PIXI.Rectangle(32,16, 16,16)),
            new PIXI.Texture(bT, new PIXI.Rectangle(48,16, 16,16)),
        ]
    }
    
    prepareRockImg() {
        return this.prepareImg("rck.png");
    }

    prepareW4Img() {
        return this.prepareImg("w4.png");
    }
    
    prepareBmbImg() {
        return this.prepareImg("bmb.png");
    }
    
    preparePtnImg() {
        return this.prepareImg("ptn.png");
    }
    
    prepareImg(imgName) {
        const bT = PIXI.BaseTexture.from(imgName);
        return [new PIXI.Texture(bT, new PIXI.Rectangle(0,0, 16,16)),]
    }
    
    drawBorder(line, viewport) {
        line.clear();
        this.drawLine(line, viewport,0,0, 0, MAP_VIEW_SIZE);
        this.drawLine(line, viewport,0,0, MAP_VIEW_SIZE, 0);
        this.drawLine(line, viewport,0,MAP_VIEW_SIZE, MAP_VIEW_SIZE, MAP_VIEW_SIZE);
        this.drawLine(line, viewport, MAP_VIEW_SIZE,0, MAP_VIEW_SIZE, MAP_VIEW_SIZE);
    }
    
    drawGrid(line, viewport) {
        const chunkSize = 8 * BLOCK_SIZE;
        
        for (let x = 0; x < MAP_VIEW_SIZE; x+=BLOCK_SIZE) {
            
            //if (x >= viewport.right || x >= viewport.bottom ) continue;
            
            if (x % chunkSize === 0) {
                this.drawLine(line, viewport, x, 0, x, MAP_VIEW_SIZE);
                this.drawLine(line, viewport, 0, x, MAP_VIEW_SIZE, x);
            } else {
                this.drawGridLine(line, viewport, x, 0, x, MAP_VIEW_SIZE);
                this.drawGridLine(line, viewport, 0, x, MAP_VIEW_SIZE, x);
            }
        }
    }
    
    drawLine(line, viewport,x0,y0,x1,y1) {
        const widthLine = 1;
        const color = 0xffffff
        
        line.lineStyle(widthLine, color, 1, 0.5,true)
            .moveTo(x0, y0)
            .lineTo(x1, y1);
    }

    drawGridLine(line, viewport,x0,y0,x1,y1) {
        const widthLine = 1;
        const color = 0xffffff;
        
        line.lineStyle(widthLine, color, 0.2, 0.5,true)
            .moveTo(x0, y0)
            .lineTo(x1, y1);
        
    }
    
    drawPathLineToPoint(path, viewport, x0, y0, x1, y1) {
        const widthLine = 5;
        const color = 0x0000FF;

        path.lineStyle(widthLine, color, 1, 0.5, true)
            .moveTo(x0, y0)
            .lineTo(x1, y1);
    }
    
    drawPathPoint(path, viewport,x0,y0) {
        const widthLine = 10;
        const color = 0xff0000

        path.beginFill(color);
        
        path.lineStyle(widthLine, color, 0.25, 0.5,true)
            .drawCircle(x0,y0, 4);
        
        path.endFill()
    }

    render() {
        const PathInspectorComponent = this.state.isPathInspectorEnabled ?
            (<PathModeInspector
                handlePathModePathEditorChanged={this.handlePathModePathEditorChanged}
                handlePathModeInspectorInit={this.handlePathModeInspectorInit}
            />)
            : (<Fragment/>);

        const ItemInspectorComponent = this.state.isItemInspectorEnabled ? 
            (<ItemModeInspector
                handleItemIdChanged={this.handleItemIdChanged}
            />) 
            : (<Fragment/>);
        
        return (
            <Fragment>
                <div id={"gridViewGl"}>
                    <canvas id={"gridCanvas"}> 
                    </canvas>
                </div>
                <div style={{textAlign: "right"}}>
                <TilePicker handleCurrentPickedTileIndex={this.handleCurrentPickedTileIndex}/>
                <TileFlipper handleFlipTile={this.handleFlipTile}/>
                <RockBrushButton
                    disableActivate={this.rockBrushButtonDisableActivate}
                    handleRockBrushActivated={this.handleRockBrushActivated}
                    
                />
                <PathModeToggler 
                    handlePathModePathEditorChanged={this.handlePathModePathEditorChanged}
                    handlePathModeInspectorInit = {this.handlePathModeInspectorInit}
                    handlePathModeTogglerChanged = {this.handlePathModeTogglerChanged}
                />
                <DownloadMapButton/>
                <ItemBrushButton 
                    handleItemBrushActivated = {this.handleItemBrushActivated}
                />
                    {PathInspectorComponent}
                    {ItemInspectorComponent}
                </div>
                <div >
               
                </div>
            </Fragment>
        );
    }
}

const ENTITY_LIST = {
    "bat": true,
    "cannon": true,
    "warlock": true,
}