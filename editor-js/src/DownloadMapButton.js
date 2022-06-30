import React from "react";

export default class DownloadMapButton extends React.Component {
    
    constructor(props) {
        super(props);
    }
    
    initMap() {
        /*for (let i = 0 ; i < 16; i++) {
            for (let j = 0 ; j < 16; j++) {
                let chunk  = '';
                
                for (let jj = 0 ; jj < 64; jj++) {
                    chunk += jj === 63 ?'0' : '0,'
                }
                
                localStorage.setItem(`${i}:${j}`,chunk)
            }
        }*/
        this.props.handleMapLoaded();
    }
    
    componentDidMount() {
        this.initMap()
    }


    render() {
        return (
            <button> Download Map</button>
        );
    };
}