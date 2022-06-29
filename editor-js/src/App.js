import './App.css';
import GridViewGl from "./gl/GridViewGl";
import DownloadMapButton from "./DownloadMapButton";

function App() {
  
    
  
  return (
    <div className="App">
        <header className={"App-header"}>
            <div style={{display: 'flex'}} >
                <GridViewGl/>
            </div>
            <DownloadMapButton/>
        </header>
    </div>
  );
}

export default App;
