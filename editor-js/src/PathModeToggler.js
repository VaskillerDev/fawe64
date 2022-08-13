import React from "react";

export default class PathModeToggler
    extends React.Component {
    
    constructor(props) {
        super(props);

        this.onPathModeClick = this.onPathModeClick.bind(this)
        
        this.state = {
            isPathMode: false,
        }
        
    }
    
    onPathModeClick(e) {
        this.setState({
            isPathMode: !this.state.isPathMode
        })
    }
    
    render() {
        const isPathMode = this.state.isPathMode ? "DarkSeaGreen" :"white"
        
        return (
            <button id={'pathModeToggler'} onClick={this.onPathModeClick} style={{backgroundColor: isPathMode}}>
                <img src={"path.png"} alt={"path"} style={{width: '64px', height: '64px'}}/>
            </button>
        );
    }
}