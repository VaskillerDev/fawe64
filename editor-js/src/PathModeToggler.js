import React from "react";
import PathModeInspector from "./PathModeInspector";

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
        const inspectorComponent = this.state.isPathMode? (<PathModeInspector/>) : (<div></div>);
        
        
        return (
            <div>
            <button id={'pathModeToggler'} onClick={this.onPathModeClick} style={{backgroundColor: isPathMode}}>
                <img src={"path.png"} alt={"path"} style={{width: '64px', height: '64px'}}/>
            </button>
                {inspectorComponent}
            </div>
        );
    }
}