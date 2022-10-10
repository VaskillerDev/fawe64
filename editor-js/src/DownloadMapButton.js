import React, {Fragment} from "react";
import {CHUNK_LEN_IN_MAP} from "./GridViewGl";

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
            
            
            for(let j = 0; j < CHUNK_LEN_IN_MAP; j++) {

                fileString += "{";
                const chunk = localStorage.getItem(`${i}:${j}`);
                fileString += chunk === "-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1" 
                    ? "2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2" 
                    : chunk;
                fileString += "},\n";
                
            }

            fileString +=  i === 7 ? "}\n" : "},\n";
        }
        
        
        fileString += "};"
        return fileString;
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