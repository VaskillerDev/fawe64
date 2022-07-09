import React, {Fragment} from "react";

const CHUNK_SIZE = 8;

export default class GridPositionComponent extends React.Component {
    
    constructor(props) {
        super(props);
    }
    
    gridPosToChunk (pos) {
        return Math.floor(pos / CHUNK_SIZE)
    }
    
    render() {
        const chunkX = this.gridPosToChunk(this.props.x)
        const chunkY = this.gridPosToChunk(this.props.y);
        
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