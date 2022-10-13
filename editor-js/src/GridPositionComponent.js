import React, {Fragment} from "react";
import gridPosToChunk from "./util/gridPosToChunk";

export default class GridPositionComponent extends React.Component {
    
    constructor(props) {
        super(props);
    }
    
    render() {
        const chunkPos = gridPosToChunk(this.props);
        const chunkX = chunkPos.x;
        const chunkY = chunkPos.y;
        
        return ( <Fragment>
        <p style={{position: "absolute", left: '32px', top: '96%', fontSize: 'small', backgroundColor: 'black'}}> 
            grid pos: ({this.props.x};{this.props.y})
        </p>
        <p style={{position: "absolute", left: '32px', top: '94%', fontSize: 'small', backgroundColor: 'black'}}>
            chunk number: ({chunkX};{chunkY})
        </p>
       </Fragment>
    );
    }
}