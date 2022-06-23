import {Fragment, Component} from "react";
import * as PIXI from 'pixi.js'

const MAP_VIEW_SIZE = 2048
const ZOOM_FACTOR = 3;

export default class GridViewGl extends Component {
    
    
    constructor() {
        super();
        this.state = {
            gridViewGlElement: undefined
        }
    }
    
    componentDidMount() {
        const gridViewGlElement = document.getElementById("gridViewGl");
        const ctx = gridViewGlElement.getContext('2d');
        ctx.imageSmoothingEnabled = false;
        
        const img = new Image();
        img.onload = function () {
            ctx.drawImage(img, 0, 0, 16, 16, 0 ,0 , 16, 16);
            
        }
        img.src = 'tiles.png'

        ctx.scale(ZOOM_FACTOR,ZOOM_FACTOR);
        
        
        ctx.translate(25,25);
        
        gridViewGlElement.addEventListener("mousemove", function (e) {
            ctx.fillStyle = "#131618";
            ctx.fillRect(0, 0, MAP_VIEW_SIZE, MAP_VIEW_SIZE);
            
            const mousePos = this.mousePos(gridViewGlElement, e);
            console.log(mousePos.x + ',' + mousePos.y);
            ctx.strokeStyle = "#ffffff";

            mousePos.x /= ZOOM_FACTOR;
            mousePos.y /= ZOOM_FACTOR;

            let gridX = Math.ceil(mousePos.x / (16 * ZOOM_FACTOR));
            let gridY = Math.ceil(mousePos.y / (16 * ZOOM_FACTOR));

            gridX =  gridX > 0  ? gridX - 1 : gridX;
            gridY = gridY > 0  ? gridY - 1 : gridY;
            
            console.log(gridX, gridY);
            
            ctx.strokeRect( gridX * 16, gridY * 16, 16, 16);

            ctx.drawImage(img, 0, 0, 16, 16, 0 ,0 , 16, 16);
        }.bind(this), false);

        ctx.fillStyle = "#131618";
        this.setState({
            gridViewGlElement
        })
        
    }

    mousePos(gridViewGlElement, e) {
        const rect = gridViewGlElement.getBoundingClientRect();
        return {
            x: (e.clientX - rect.left ),
            y: (e.clientY - rect.top)
        };
    }

    render() {
        console.log("render")
        return (
            <Fragment>
                <canvas id={"gridViewGl"} width={MAP_VIEW_SIZE} height={MAP_VIEW_SIZE} >

                </canvas>
            </Fragment>
        );
    }
}



