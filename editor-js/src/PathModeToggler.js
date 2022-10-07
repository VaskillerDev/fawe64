import React from "react";
import PathModeInspector from "./PathModeInspector";

export default class PathModeToggler
    extends React.Component {

    handlePathModePathEditorChanged(text) {
        try {
            const dataArr = text.toLowerCase().split('->'); // "bat->(0;0)->(1;0)->(2;2)"

            const entityId = dataArr[0]; // 'bat'
            if (!ENTITY_LIST[entityId]) return; 
            
            const len = dataArr.length;
            let gridPosArr = [];
            for (let i = 1; i < len; i++) {
                const rawPos = dataArr[i] // '(0;0)'
                if (rawPos === '') return;
                const pos = this.rawPosToNormalPos(rawPos);
                if (!pos) return;
                gridPosArr.push(pos);
            }
            
            this.props.handlePathModePathEditorChanged(entityId, gridPosArr);
        } catch (e) {}
        
    }

    rawPosToNormalPos(rawPos) {
        const lastChar = rawPos.length-1;
        if (!(rawPos.charAt(0) === '(' && rawPos.charAt(lastChar) === ')')) return;
        
        let pos = rawPos.substring(1, lastChar).split(';');
        return {x: Number.parseInt(pos[0]), y: Number.parseInt(pos[1])};
    }
    
    constructor(props) {
        super(props);

        this.onPathModeClick = this.onPathModeClick.bind(this)
        this.handlePathModePathEditorChanged = this.handlePathModePathEditorChanged.bind(this);
        
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
        const inspectorComponent = this.state.isPathMode? 
            (<PathModeInspector handlePathModePathEditorChanged={this.handlePathModePathEditorChanged}/>) 
            : (<div></div>);
        
        
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

const ENTITY_LIST = {
    "bat": true,
    "cannon": true,
    "warlock": true,
}