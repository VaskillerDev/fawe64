import './App.css';
import GridViewGl from "./GridViewGl";
import React from "react";
import GridPositionComponent from "./GridPositionComponent";
import SaveLocalStorage from "./SaveLocalStorage";
import LoadToLocalStorage from "./LoadToLocalStorage";

window.Save = SaveLocalStorage;
window.Load = LoadToLocalStorage;

class App extends React.Component {


    handleGridPositionChanged(gridX, gridY) {
        this.setState({
            currentGridX: gridX,
            currentGridY: gridY,
        })
    }
    
    constructor(props) {
        super(props);

        this.handleGridPositionChanged = this.handleGridPositionChanged.bind(this);
        
        this.state = {
            currentGridX: 0,
            currentGridY: 0,
        }
    }

    render() {
         return (
             <div className="App">
                 <header className={"App-header"}>
                     <div style={{display: 'flex'}} >
                         <GridViewGl 
                             handleGridPositionChanged={this.handleGridPositionChanged}
                         />
                     </div>
                     
                     <GridPositionComponent 
                         x={this.state.currentGridX}
                         y={this.state.currentGridY} 
                     />
                 </header>
             </div>
         );
     }
}

export default App;
