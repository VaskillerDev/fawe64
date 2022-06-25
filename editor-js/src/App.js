import './App.css';
import GridViewGl from "./gl/GridViewGl";

function App() {
  return (
    <div className="App">
        <header className={"App-header"}>
            <div style={{display: 'flex', marginRight: '256px'}} >
                <img src={"tiles.png"} style={{width: 256, height: 128, imageRendering: 'pixelated' }}/>
                <GridViewGl/>
            </div>
        </header>
    </div>
  );
}

export default App;
