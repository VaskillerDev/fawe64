import React, {Fragment} from "react";

export default class RockBrushButton extends React.Component {

    constructor(props) {
        super(props);

        this.onActivateClick = this.onActivateClick.bind(this);
        
        this.state = {
            isActivate: false,
        }
    }

    componentDidMount() {
        const body = document.body
        let isActivate;
        body.addEventListener("keyup", (e) => {
            const {key} = e;

            if (key.toLowerCase() === 'r') {
                this.setState({
                    isActivate: !this.state.isActivate
                });
                isActivate = this.state.isFlipH;
            }
        })
    }
    
    onActivateClick(_) {
        this.setState({isActivate: !this.state.isActivate})

        this.props.handleRockBrushActivated(!this.state.isActivate);
    }
    
    render() {
        let isActivate = this.state.isActivate ? "DarkSeaGreen" :"white"

        isActivate = this.props.disableActivate ? false : isActivate
        
        return (
            <Fragment>
                <button id={'rockBrushButton'} onClick={this.onActivateClick} style={{backgroundColor: isActivate}}>
                    <img src={"rock.png"} alt={"path"} style={{width: '64px', height: '64px'}}/>
                </button>
            </Fragment>
        );
    };
}