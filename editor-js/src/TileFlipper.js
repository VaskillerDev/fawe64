import {Component, Fragment} from "react";

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
    }
    
    componentDidMount() {
        const body = document.body
        body.addEventListener("keyup", (e) => {
            const {key} = e;
            let flipIndex;
            let isFlip;
            
            if (key.toLowerCase() === 'h') {
                flipIndex = 0;
                this.setState({
                    isFlipH: !this.state.isFlipH
                });
                isFlip = this.state.isFlipH;
            }

            if (key.toLowerCase() === 'v') {
                flipIndex = 1;
                this.setState({
                    isFlipV: !this.state.isFlipV
                });
                isFlip = this.state.isFlipV;
            }

            if (key.toLowerCase() === 'r') {
                flipIndex = 2;
                this.setState({
                    isFlipD: !this.state.isFlipD
                });
                isFlip = this.state.isFlipD;
            }
            this.props.handleFlipTile(flipIndex, isFlip)
        })
    }

    render() {
        
        const flipHColor = this.state.isFlipH ? "DarkSeaGreen" :"white"
        const flipVColor = this.state.isFlipV ? "DarkSeaGreen" : "white"
        const flipDColor = this.state.isFlipD ? "DarkSeaGreen" :"white"
        
        return (
            <div id={"tileFlipper"}>
            <button id={'flipH'} onClick={this.onFlipClick} style={{backgroundColor: flipHColor}}>
                <img src={"flipH.png"} alt={"flipH"} style={{width: '64px', height: '64px'}}/>
            </button>
                <button id={'flipV'} onClick={this.onFlipClick} style={{backgroundColor: flipVColor}} >
                    <img src={"flipV.png"} alt={"flipV"} style={{width: '64px', height: '64px'}}/>
                </button>
                <button id={'flipD'} onClick={this.onFlipClick} style={{backgroundColor: flipDColor}}>
                    <img src={"flipD.png"} alt={"flipD"} style={{width: '64px', height: '64px'}}/>
                </button>
            </div>
        );
    }
}