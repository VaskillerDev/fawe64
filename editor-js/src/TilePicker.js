import {Component, Fragment} from "react";

const BORDER_WIDTH = 4;
const BLOCK_DISPLAY_SIZE = 16 * 4

export default class TilePicker extends Component {
    
    tilePicker;
    tilePickerCursor;
    
    constructor(props) {
        super(props);
        this.state = {currentPickedTileIndex: 0}
    }
    
    componentDidMount() {
        this.tilePicker = document.getElementById("tilePicker");
        this.tilePickerCursor = document.getElementById("tilePickerCursor");
        this.tilePickerCursor.style.border = `${BORDER_WIDTH}px solid #4E6BE3`;
        
        console.log(document.getElementById("gridViewGlComponent"));
        
        this.tilePicker.addEventListener('click', e =>{
            const {clientX, clientY} = e;
            const rect = this.tilePicker.getBoundingClientRect();
            let tileGridX = Math.ceil((clientX - rect.left) / BLOCK_DISPLAY_SIZE);
            let tileGridY = Math.ceil((clientY - rect.top) / BLOCK_DISPLAY_SIZE);
            
            tileGridX =  tileGridX > 0  ? tileGridX - 1 : tileGridX;
            tileGridY = tileGridY > 0  ? tileGridY - 1 : tileGridY
            
            /*console.log(e);
            console.log(tileGridX ,tileGridY )
            console.log(this.tilePicker.getBoundingClientRect().left, this.tilePicker.getBoundingClientRect().top);*/

            this.tilePickerCursor.style.display = 'inline'
            this.tilePickerCursor.style.left = (rect.left + tileGridX * BLOCK_DISPLAY_SIZE - BORDER_WIDTH) + 'px';
            this.tilePickerCursor.style.top = (rect.top + tileGridY * BLOCK_DISPLAY_SIZE - BORDER_WIDTH) + 'px';
            
            const currentPickedTileIndex = tileGridX + tileGridY * 4 ;
            
            this.setState({
                currentPickedTileIndex
            });
            
            this.props.handleCurrentPickedTileIndex(currentPickedTileIndex);
        });
    }
    
    render() {
        return (
            <Fragment>
                <div id={"tilePickerCursor"} style={{width: 64, height: 64, position: 'absolute', display: 'none' }}/>
                <img id={"tilePicker"} src={"tiles.png"} style={{width: 256, height: 128, imageRendering: 'pixelated', marginLeft: '32px' }} alt={""}/>
                <p>{this.state.currentPickedTileIndex}</p>
            </Fragment>
        );
    }
}