import React from "react";
import PathModeInspectorPathEditor from "./PathModeInspectorPathEditor";

export default class PathModeInspector extends React.Component {
    
    constructor(props) {
        super(props);
        this.handlePathModePathEditorChanged = this.handlePathModePathEditorChanged.bind(this);
    }

    handlePathModePathEditorChanged(text) {
        this.props.handlePathModePathEditorChanged(text);
    }
    
    render() {
        return (
            <nav className={"App-path-mode-inspector"}>
                <h1> Inspector</h1>
                <p style={{fontSize: "x-small"}}>bat->(0;0)->(1;0)->(2;2)</p>
            <ol>
            <PathModeInspectorPathEditor handlePathModePathEditorChanged={this.handlePathModePathEditorChanged}/>
            <PathModeInspectorPathEditor/>
    </ol>
    </nav>)
    }
}