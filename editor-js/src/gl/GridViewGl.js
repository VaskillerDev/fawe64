import {Fragment, Component} from "react";
import * as PIXI from 'pixi.js'
import {Viewport} from "pixi-viewport";
import TilePicker from "../TilePicker";

const MAP_VIEW_SIZE = 2048
const ZOOM_FACTOR = 2;
const BLOCK_SIZE = 16;

export default class GridViewGl extends Component {
    
    app;
    currentPickedTileIndex = 0;

    handleCurrentPickedTileIndex( index) {
        this.currentPickedTileIndex = index;
    }
    
    constructor(props) {
        super(props);
        
        this.handleCurrentPickedTileIndex = this.handleCurrentPickedTileIndex.bind(this);
    }
    
    componentDidMount() {
        PIXI.settings.SCALE_MODE = PIXI.SCALE_MODES.NEAREST;
        this.app = new PIXI.Application({
            width: window.innerWidth - 512,
            height: window.innerHeight - 256,
            view: document.getElementById("gridCanvas"),
            backgroundColor:  0x282c34,
            clearBeforeRender: true
        });
        
        document.getElementById("gridViewGl").appendChild(this.app.view)

        const viewport = new Viewport({
            screenWidth: MAP_VIEW_SIZE,
            screenHeight: MAP_VIEW_SIZE,
            worldWidth: MAP_VIEW_SIZE,
            worldHeight: MAP_VIEW_SIZE,
            
            interaction: this.app.renderer.plugins.interaction
        })
        
        const mouseCursorBlock = viewport.addChild(new PIXI.Sprite(PIXI.Texture.WHITE))
        mouseCursorBlock.tint = 0x4E6BE3
        mouseCursorBlock.width = mouseCursorBlock.height = BLOCK_SIZE
        mouseCursorBlock.position.set(0, 0)
        mouseCursorBlock.alpha = 0.45

        const borderLine = new PIXI.Graphics();
        const gridLine = new PIXI.Graphics();
        viewport.addChild(borderLine);
        viewport.addChild(gridLine);
        
        viewport.addListener("mousemove", (e)=> {
            let mousePos = viewport.toWorld(e.data.global.x, e.data.global.y)
            
            if (Number.isNaN(mousePos.x)) return
            
            let gridX = Math.ceil(mousePos.x / BLOCK_SIZE);
            let gridY = Math.ceil(mousePos.y / BLOCK_SIZE);

            gridX =  gridX > 0  ? gridX - 1 : gridX;
            gridY = gridY > 0  ? gridY - 1 : gridY

            mouseCursorBlock.position.set(BLOCK_SIZE * gridX, BLOCK_SIZE * gridY)
        })
        
        viewport.addListener('clicked', (e)=> {
            console.log(e);
            let mousePos = viewport.toWorld(e.event.data.global.x, e.event.data.global.y)
            if (Number.isNaN(mousePos.x)) return
            let gridX = Math.ceil(mousePos.x / BLOCK_SIZE);
            let gridY = Math.ceil(mousePos.y / BLOCK_SIZE);

            gridX =  gridX > 0  ? gridX - 1 : gridX;
            gridY = gridY > 0  ? gridY - 1 : gridY
            
            console.log(gridX, gridY);
            
            this.spawnTile(tiles, viewport, this.currentPickedTileIndex, gridX, gridY, true, false, true);
        });
        
        
        
        this.app.stage.addChild(viewport)
        

        viewport
            .drag()
            .pinch()
            .wheel()
            .decelerate()

        viewport.fit()

        const tiles = this.prepareAtlas();
        
        this.drawBorder(borderLine, viewport)
        this.drawGrid(gridLine, viewport)
    }
    
    spawnTile(tiles, viewport, tileId, gridX, gridY, isFlipH, isFlipV, isFlipD) {
        const sprite = viewport.addChild(new PIXI.Sprite(tiles[tileId]))
        sprite.width = sprite.height = BLOCK_SIZE
        sprite.position.set(BLOCK_SIZE * gridX, BLOCK_SIZE * gridY);
        sprite.scale.x = isFlipH? -1 : 1;
        sprite.scale.y = isFlipV? -1 : 1;
        sprite.anchor.x = 0.5
        sprite.anchor.y = 0.5
        sprite.rotation = isFlipD? (3. * Math.PI / 2) : 0;
        

        sprite.position.set( sprite.position.x + BLOCK_SIZE / 2,  sprite.position.y + BLOCK_SIZE / 2);
    }
    
    prepareAtlas() {
        const bT = PIXI.BaseTexture.from('tiles.png');
        
        return [
            new PIXI.Texture(bT, new PIXI.Rectangle(0,0, 16,16)),
            new PIXI.Texture(bT, new PIXI.Rectangle(16,0, 16,16)),
            new PIXI.Texture(bT, new PIXI.Rectangle(32,0, 16,16)),
            new PIXI.Texture(bT, new PIXI.Rectangle(48,0, 16,16)),

            new PIXI.Texture(bT, new PIXI.Rectangle(0,16, 16,16)),
            new PIXI.Texture(bT, new PIXI.Rectangle(16,16, 16,16)),
            new PIXI.Texture(bT, new PIXI.Rectangle(32,16, 16,16)),
            new PIXI.Texture(bT, new PIXI.Rectangle(48,16, 16,16)),
        ]
    }
    
    
    
    drawBorder(line, viewport) {
        line.clear();
        this.drawLine(line, viewport,0,0, 0, MAP_VIEW_SIZE);
        this.drawLine(line, viewport,0,0, MAP_VIEW_SIZE, 0);
        this.drawLine(line, viewport,0,MAP_VIEW_SIZE, MAP_VIEW_SIZE, MAP_VIEW_SIZE);
        this.drawLine(line, viewport, MAP_VIEW_SIZE,0, MAP_VIEW_SIZE, MAP_VIEW_SIZE);
    }
    
    drawGrid(line, viewport) {
        const chunkSize = 8 * BLOCK_SIZE;

        const viewportPointRB = viewport.toWorld(viewport.right, viewport.bottom)
        
        console.log(viewport.right)
        
        for (let x = 0; x < MAP_VIEW_SIZE; x+=BLOCK_SIZE) {
            
            //if (x >= viewport.right || x >= viewport.bottom ) continue;
            
            if (x % chunkSize === 0) {
                this.drawLine(line, viewport, x, 0, x, MAP_VIEW_SIZE);
                this.drawLine(line, viewport, 0, x, MAP_VIEW_SIZE, x);
            } else {
                this.drawGridLine(line, viewport, x, 0, x, MAP_VIEW_SIZE);
                this.drawGridLine(line, viewport, 0, x, MAP_VIEW_SIZE, x);
            }
        }

        
    }
    
    drawLine(line, viewport,x0,y0,x1,y1) {
        const widthLine = 1;
        const color = 0xffffff
        
        line.lineStyle(widthLine, color, 1, 0.5,true)
            .moveTo(x0, y0)
            .lineTo(x1, y1);
    }

    drawGridLine(line, viewport,x0,y0,x1,y1) {
        const widthLine = 1;
        const color = 0xffffff
        
        line.lineStyle(widthLine, color, 0.2, 0.5,true)
            .moveTo(x0, y0)
            .lineTo(x1, y1);
        
    }

    render() {
        console.log("render")
        return (
            <Fragment>
                <div id={"gridViewGl"}>
                    <canvas id={"gridCanvas"}> 
                    </canvas>
                </div>
                <TilePicker handleCurrentPickedTileIndex={this.handleCurrentPickedTileIndex}/>
            </Fragment>
        );
    }
}



