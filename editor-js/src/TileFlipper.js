﻿import {Component, Fragment} from "react";

export default class TileFlipper extends Component {
    constructor(props) {
        super(props);
        
        this.onFlipClick = this.onFlipClick.bind(this);
        
        this.state = {
            isFlipH: false,
            isFlipV: false,
            isFlipD: false
        }
    }
    
    onFlipClick(e) {
        const {target} = e;
        let flipIndex;
        let isFlip;
        
        switch (target.alt) {
            case "flipH": {
                flipIndex = 0;
                this.setState({
                    isFlipH: !this.state.isFlipH
                });
                isFlip = !this.state.isFlipH;
            } break;
            case "flipV": {
                flipIndex = 1;
                this.setState({
                    isFlipV: !this.state.isFlipV
                });
                isFlip = !this.state.isFlipV;
            } break;
            case "flipD": {
                flipIndex = 2;
                this.setState({
                    isFlipD: !this.state.isFlipD
                });
                isFlip = !this.state.isFlipD;
            } break;
        }
        this.props.handleFlipTile(flipIndex, isFlip)
        console.log(flipIndex);
    }
    
    render() {
        
        const flipHColor = this.state.isFlipH ? "black" :"white"
        const flipVColor = this.state.isFlipV ? "black" : "white"
        const flipDColor = this.state.isFlipD ? "black" :"white"
        
        return (
            <Fragment>
            <button id={'flipH'} onClick={this.onFlipClick} style={{backgroundColor: flipHColor}}>
                <img src={"flipH.png"} alt={"flipH"} style={{width: '64px', height: '64px',  imageRendering: 'pixelated'}}/>
            </button>
                <button id={'flipV'} onClick={this.onFlipClick} style={{backgroundColor: flipVColor}} >
                    <img src={"flipV.png"} alt={"flipV"} style={{width: '64px', height: '64px',  imageRendering: 'pixelated'}}/>
                </button>
                <button id={'flipD'} onClick={this.onFlipClick} style={{backgroundColor: flipDColor}}>
                    <img src={"flipD.png"} alt={"flipD"} style={{width: '64px', height: '64px',  imageRendering: 'pixelated'}}/>
                </button>
            </Fragment>
        );
    }
}