import './App.css';
import GridViewGl from "./gl/GridViewGl";
import TilePicker from "./TilePicker";

function App() {
  
    
  
  return (
    <div className="App">
        <header className={"App-header"}>
            <div style={{display: 'flex'}} >
                <GridViewGl/>
            </div>
        </header>
    </div>
  );
}

export default App;
