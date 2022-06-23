import {Fragment, Component} from "react";
import * as PIXI from 'pixi.js'
import {Viewport} from "pixi-viewport";

const MAP_VIEW_SIZE = 2048
const ZOOM_FACTOR = 2;

export default class GridViewGl extends Component {
    
    app;
    
    constructor() {
        super();
        
        this.state = {
            gridViewGlElement: undefined
        }
    }
    
    componentDidMount() {
        console.log("mounted");
        this.app = new PIXI.Application();
        /*const gridViewGlElement = document.getElementById("gridViewGl");
        const ctx = gridViewGlElement.getContext('2d');
        ctx.imageSmoothingEnabled = false;
        
        const img = new Image();
        img.onload = function () {
            ctx.drawImage(img, 0, 0, 16, 16, 0 ,0 , 16, 16);
            
        }
        img.src = 'tiles.png'

        ctx.scale(ZOOM_FACTOR,ZOOM_FACTOR);
        
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
        })*/

        
        document.getElementById("gridViewGl").appendChild(this.app.view)

        const viewport = new Viewport({
            screenWidth: 3000,
            screenHeight: 720,
            worldWidth: MAP_VIEW_SIZE,
            worldHeight: MAP_VIEW_SIZE,

            interaction: this.app.renderer.plugins.interaction
        })

        this.app.stage.addChild(viewport)

        viewport
            .drag()
            .pinch()
            .wheel()
            .decelerate()

        const sprite = viewport.addChild(new PIXI.Sprite(PIXI.Texture.WHITE))
        sprite.tint = 0xff0000
        sprite.width = sprite.height = 100
        sprite.position.set(100, 100)
        
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
                <div id={"gridViewGl"} style={{width: 3000}}>
                </div>
            </Fragment>
        );
    }
}



