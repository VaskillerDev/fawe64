import React, {Fragment} from "react";

export default class ItemBrushButton extends React.Component {

    isActivate = false;
    
    constructor(props) {
        super(props);

        this.onActivateClick = this.onActivateClick.bind(this);
    }

    componentDidMount() {
        const body = document.body
        body.addEventListener("keyup", (e) => {
            const {key} = e;

            if (key.toLowerCase() === 't') this.toggleActivate();
        })
    }

    toggleActivate() {
        this.isActivate = !this.isActivate;
    }
    
    onActivateClick(_) {
        this.toggleActivate()
        this.props.handleItemBrushActivated(this.isActivate);
        
        this.forceUpdate();
    }

    render() {
        let backgroundColor = this.props.isPicked && this.isActivate  ? "DarkSeaGreen" :"white";
        
        return (
            <Fragment>
                <button id={'itemBrushButton'} onClick={this.onActivateClick} style={{backgroundColor}}>
                    <img src={"sword.png"} alt={"path"} style={{width: '64px', height: '64px'}}/>
                </button>
            </Fragment>
        );
    };
}