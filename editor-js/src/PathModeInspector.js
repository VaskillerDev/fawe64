import React from "react";
import PathModeInspectorPathEditor from "./PathModeInspectorPathEditor";

export const PATH_TEXT_ARR_KEY = "pathTextArr";

export default class PathModeInspector extends React.Component {
    
    constructor(props) {
        super(props);
        this.handlePathModePathEditorChanged = this.handlePathModePathEditorChanged.bind(this);
        this.handlePathModeInspectorPathEditorInit = this.handlePathModeInspectorPathEditorInit.bind(this);
    }
    
    getPathTextArr() {
        const rawPathTextArr = localStorage.getItem(PATH_TEXT_ARR_KEY) ?? [];
        return typeof rawPathTextArr === "string"
            ? JSON.parse(rawPathTextArr)
            : rawPathTextArr;
    }
    
    savePathTextArr(count, text) {
        const pathTextArr = this.getPathTextArr();
        pathTextArr[count] = text;
        localStorage.setItem(PATH_TEXT_ARR_KEY, JSON.stringify(pathTextArr));
    }

    handlePathModeInspectorPathEditorInit(count) {
        const pathTextArr = this.getPathTextArr();

        const inspectorPathEditorList = document.getElementById("inspector-path-editor-list");
        
        for (const elem of inspectorPathEditorList.children) {
            if (elem.nodeName === "DD") {
                const inputElem = elem.firstChild;
                if (inputElem.id !== ""+count) continue;
                inputElem.value = pathTextArr[count] ?? "";
                this.props.handlePathModePathEditorChanged(count, inputElem.value);
            }
        }
    }
    
    handlePathModePathEditorChanged(count, text) {
        this.props.handlePathModePathEditorChanged(count, text);
        this.savePathTextArr(count, text);
    }
    
    render() {
        let pathModeInspectorPathEditorList = [];
        for (let i = 0; i < 32; i++) {
            pathModeInspectorPathEditorList.push(i);
        }
        
        return (
            <nav className={"App-path-mode-inspector"}>
                <h1>Inspector</h1>
                <p style={{fontSize: "x-small"}}>bat->(0;0)->(1;0)->(2;2)</p>
            <dl id={`inspector-path-editor-list`}>
                {pathModeInspectorPathEditorList.map(i => {
                    return (<PathModeInspectorPathEditor
                                                         key={i}   
                                                         id={`inspector-path-editor-${i}`} 
                                                         count={i}
                                                         handlePathModeInspectorPathEditorInit={this.handlePathModeInspectorPathEditorInit}
                                                         handlePathModePathEditorChanged={this.handlePathModePathEditorChanged}
                        />)})}
    </dl>
    </nav>)
    }
}