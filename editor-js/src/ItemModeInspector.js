import React from "react";
import itemIdToNumber from "./util/itemIdToNumber";

export const ITEM_TEXT_ARR_KEY = "itemTextArr";

export default class ItemModeInspector extends React.Component {

    constructor(props) {
        super(props);
        
        this.onChange = this.onChange.bind(this);
    }
    
    onChange(e) {
        const idx = e.target.selectedIndex;
        const option = e.target.options[idx];
        const name = option.innerText;
        
        const itemIdNum = itemIdToNumber[name];
        
        this.props.handleItemIdChanged(itemIdNum);
    }
    
    render() {
        return (
            <nav className={"App-path-mode-inspector"}>
                <h1>Items</h1>
                <select id="item-select" onChange={this.onChange}>
                    <option value="Potion">Potion</option>
                    <option value="Bomb">Bomb</option>
                    <option value="DirectedBomb">DirectedBomb</option>
                    <option defaultValue="Unknown">Unknown</option>
                </select>
            </nav>)
    }
}