import React from "react";

export default class PathModeInspectorPathEditor extends React.Component {

    handlePathModePathEditorChanged(e) {
        if (!this.props.handlePathModePathEditorChanged) return;
        this.props.handlePathModePathEditorChanged(e.target.value);
    }
    
    constructor(props) {
        super(props);
        this.handlePathModePathEditorChanged = this.handlePathModePathEditorChanged.bind(this);
    }
    
    
    render() {
        return (
            <li className={"App-path-mode-inspector-path-editor"}>
            <input type={"text"} onChange={this.handlePathModePathEditorChanged} ></input>
            </li>
        );
    }
}