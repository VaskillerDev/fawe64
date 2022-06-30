import {Fragment, Component} from "react";
import * as PIXI from 'pixi.js'
import {Viewport} from "pixi-viewport";
import DownloadMapButton from "./DownloadMapButton";
import TilePicker from "./TilePicker";
import TileFlipper from "./TileFlipper";

const MAP_VIEW_SIZE = 2048
const ZOOM_FACTOR = 2;
const BLOCK_SIZE = 16;

export default class GridViewGl extends Component {
    
    app;
    currentPickedTileIndex = 0;

    currentPickedTileIsFlipH = false;
    currentPickedTileIsFlipV = false;
    currentPickedTileIsFlipD = false;

    tiles;
    viewport;
    mouseCursorBlock;

    isBrushMode = false;

    handleMapLoaded() {
        for (let i = 0 ; i < 16; i++) {
            for (let j = 0 ; j < 16; j++) {
                const chunk = localStorage.getItem(`${i}:${j}`);
                const chunkData = chunk.split(',')

                let offset = 0;
                for (const tile of chunkData) {
                    const tileInt = Number.parseInt(tile);
                    if (tileInt === 0) {
                        ++offset;
                        continue;
                    }
                    
                    let x = (i * 8 + offset) % 8
                    let y = (j * 8 ) % 8 // todo
                    
                    
                    this.spawnTile(this.tiles, this.viewport, 0, x, y)
                    ++offset;
                }
            }
        }
    }
    
    handleCurrentPickedTileIndex(index) {
        this.currentPickedTileIndex = index;

        this.setMouseCursorBlock(this.tiles,
            this.currentPickedTileIndex,
            this.currentPickedTileIsFlipH,
            this.currentPickedTileIsFlipV,
            this.currentPickedTileIsFlipD);
    }

    handleFlipTile(indexFlip, isFlip) {
        
        switch (indexFlip) {
            case 0: { this.currentPickedTileIsFlipH = isFlip; break; }
            case 1: { this.currentPickedTileIsFlipV = isFlip; break; }
            case 2: { this.currentPickedTileIsFlipD = isFlip; break; }
        }
        
        this.setMouseCursorBlock(this.tiles,
            this.currentPickedTileIndex,
            this.currentPickedTileIsFlipH,
            this.currentPickedTileIsFlipV,
            this.currentPickedTileIsFlipD);
    }
    
    constructor(props) {
        super(props);
        
        this.handleCurrentPickedTileIndex = this.handleCurrentPickedTileIndex.bind(this);
        this.handleMapLoaded = this.handleMapLoaded.bind(this);
        this.handleFlipTile = this.handleFlipTile.bind(this);
        
        this.state = {
            downloadMapButton: <div>Empty</div>
        }
        
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

        this.viewport = viewport;
        
        const borderLine = new PIXI.Graphics();
        const gridLine = new PIXI.Graphics();
        viewport.addChild(borderLine);
        viewport.addChild(gridLine);
        
        viewport.sortableChildren = true;

        viewport.addListener("mousemove", (e)=> {
            let mousePos = viewport.toWorld(e.data.global.x, e.data.global.y)
            
            if (Number.isNaN(mousePos.x)) return
            
            let gridX = Math.ceil(mousePos.x / BLOCK_SIZE);
            let gridY = Math.ceil(mousePos.y / BLOCK_SIZE);

            gridX =  gridX > 0  ? gridX - 1 : gridX;
            gridY = gridY > 0  ? gridY - 1 : gridY
            
            this.mouseCursorBlock.position.set(BLOCK_SIZE * gridX + BLOCK_SIZE / 2, BLOCK_SIZE * gridY + BLOCK_SIZE / 2)
            
            if (!this.isBrushMode) return;

            this.spawnTile(this.tiles,
                viewport,
                this.currentPickedTileIndex,
                gridX,
                gridY,
                this.currentPickedTileIsFlipH,
                this.currentPickedTileIsFlipV,
                this.currentPickedTileIsFlipD);
        })
        
        const canvas = document.getElementById("gridCanvas");

        canvas.addEventListener('mousedown', (e)=>{
            if (e.button === 0) {
                this.isBrushMode = true;
            }
        })

        canvas.addEventListener('mouseup', (e)=>{
            if (e.button === 0) {
                this.isBrushMode = false;
            }
        })
        
        
        viewport.addListener('clicked', (e)=> {
            
            let mousePos = viewport.toWorld(e.event.data.global.x, e.event.data.global.y)
            if (Number.isNaN(mousePos.x)) return
            let gridX = Math.ceil(mousePos.x / BLOCK_SIZE);
            let gridY = Math.ceil(mousePos.y / BLOCK_SIZE);

            gridX =  gridX > 0  ? gridX - 1 : gridX;
            gridY = gridY > 0  ? gridY - 1 : gridY
            
            // console.log(gridX, gridY);
            
            this.spawnTile(this.tiles,
                viewport,
                this.currentPickedTileIndex,
                gridX,
                gridY,
                this.currentPickedTileIsFlipH,
                this.currentPickedTileIsFlipV,
                this.currentPickedTileIsFlipD);
        });

        
        
        this.app.stage.addChild(viewport)

        viewport
            .drag({
                mouseButtons: 'middle'
            })
            .pinch()
            .wheel()
            .decelerate()

        viewport.fit()

        this.tiles = this.prepareAtlas();

        this.initMouseCursorBlock(viewport);
        this.setMouseCursorBlock(this.tiles, 0, 
            this.currentPickedTileIsFlipH,
            this.currentPickedTileIsFlipV,
            this.currentPickedTileIsFlipD);
        
        this.drawBorder(borderLine, viewport)
        this.drawGrid(gridLine, viewport)
        
        this.setState({
            downloadMapButton: <DownloadMapButton handleMapLoaded={this.handleMapLoaded}/>
        })
    }
    
    initMouseCursorBlock(viewport) {
        this.mouseCursorBlock = viewport.addChild(new PIXI.Sprite(PIXI.Texture.WHITE))
        this.mouseCursorBlock.width = this.mouseCursorBlock.height = BLOCK_SIZE
        this.mouseCursorBlock.position.set(0, 0)
        this.mouseCursorBlock.alpha = 0.45
        this.mouseCursorBlock.zIndex = 1;
    }
    
    setMouseCursorBlock(tiles, tileId, isFlipH, isFlipV, isFlipD) {
        this.mouseCursorBlock.texture = tiles[tileId];
        this.mouseCursorBlock.scale.x = isFlipH? -1 : 1;
        this.mouseCursorBlock.scale.y = isFlipV? -1 : 1;
        this.mouseCursorBlock.anchor.x = 0.5
        this.mouseCursorBlock.anchor.y = 0.5
        this.mouseCursorBlock.rotation = isFlipD? (3. * Math.PI / 2) : 0;
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
        sprite.zIndex = -1;
        

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
        return (
            <Fragment>
                <div id={"gridViewGl"}>
                    <canvas id={"gridCanvas"}> 
                    </canvas>
                </div>
                <div>
                <TilePicker handleCurrentPickedTileIndex={this.handleCurrentPickedTileIndex}/>
                <TileFlipper handleFlipTile={this.handleFlipTile}/>
                </div>
                {this.state.downloadMapButton}
            </Fragment>
        );
    }
}



