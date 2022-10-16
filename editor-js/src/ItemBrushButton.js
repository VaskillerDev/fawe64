import React, {Fragment} from "react";

export default class ItemBrushButton extends React.Component {

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

            if (key.toLowerCase() === 't') {
                this.setState({
                    isActivate: !this.state.isActivate
                });
                isActivate = this.state.isActivate;
            }
        })
    }

    onActivateClick(_) {
        this.setState({isActivate: !this.state.isActivate});
        
        this.props.handleItemBrushActivated(!this.state.isActivate);
    }

    render() {
        let isActivate = this.state.isActivate ? "DarkSeaGreen" :"white"
        
        return (
            <Fragment>
                <button id={'itemBrushButton'} onClick={this.onActivateClick} style={{backgroundColor: isActivate}}>
                    <img src={"sword.png"} alt={"path"} style={{width: '64px', height: '64px'}}/>
                </button>
            </Fragment>
        );
    };
}