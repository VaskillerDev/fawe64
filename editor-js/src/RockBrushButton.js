import React, {Fragment} from "react";

export default class RockBrushButton extends React.Component {

    isActivate = false;
    
    constructor(props) {
        super(props);

        this.onActivateClick = this.onActivateClick.bind(this);
    }

    componentDidMount() {
        const body = document.body
        body.addEventListener("keyup", (e) => {
            const {key} = e;
            if (key.toLowerCase() === 'r') this.toggleActivate()
        })
    }

    toggleActivate() {
        this.isActivate = !this.isActivate;
    }
    
    onActivateClick(_) {
        this.toggleActivate()
        this.props.handleRockBrushActivated(this.isActivate);
    }
    
    render() {
        let backgroundColor = this.props.isPicked && this.isActivate  ? "DarkSeaGreen" :"white";
        //isActivate = this.props.disableActivate ? false : isActivate
        
        return (
            <Fragment>
                <button id={'rockBrushButton'} onClick={this.onActivateClick} style={{backgroundColor}}>
                    <img src={"rock.png"} alt={"path"} style={{width: '64px', height: '64px'}}/>
                </button>
            </Fragment>
        );
    };
}