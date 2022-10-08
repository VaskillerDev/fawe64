import React, {Fragment} from "react";

export default class PathModeInspectorPathEditor extends React.Component {
    
    handlePathModePathEditorChanged(e) {
        if (!this.props.handlePathModePathEditorChanged) return;
        this.props.handlePathModePathEditorChanged(this.props.count, e.target.value);
    }
    
    handlePathModeInspectorPathEditorInit() {
        if (!this.props.handlePathModeInspectorPathEditorInit) return;
        this.props.handlePathModeInspectorPathEditorInit(this.props.count);
    }
    
    constructor(props) {
        super(props);
        this.handlePathModePathEditorChanged = this.handlePathModePathEditorChanged.bind(this);
        this.handlePathModeInspectorPathEditorInit = this.handlePathModeInspectorPathEditorInit.bind(this);
    }
    
    componentDidMount() {
        this.handlePathModeInspectorPathEditorInit();
    }

    render() {
        return (
            <Fragment>
            <dt>{this.props.count}</dt>
            <dd className={"App-path-mode-inspector-path-editor"}>
            <input id={this.props.count} type={"text"} onChange={this.handlePathModePathEditorChanged} ></input>
            </dd>
            </Fragment>
        );
    }
}