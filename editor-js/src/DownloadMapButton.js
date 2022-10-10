import React, {Fragment} from "react";

export default class DownloadMapButton extends React.Component {
    
    constructor(props) {
        super(props);
    }

    onDownloadMapClick(_) {
        
    }
    
    render() {
        return (
            <Fragment>
                <button id={'downloadMapButton'} onClick={this.onDownloadMapClick}>
                    <img src={"save.png"} alt={"path"} style={{width: '64px', height: '64px'}}/>
                </button>
            </Fragment>
        );
    };
}