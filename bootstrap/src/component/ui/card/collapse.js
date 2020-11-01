import React from 'react';
import Dropdown from '../dropdown';
import Reacts from '../../../util/reacts';
import Strings from '../../../util/strings';
import Bootstraps from '../../../util/bootstraps';

export default class CollapseCard extends React.Component {
    constructor(props) {
        super(props);

        this.state = {
            visible: true
        }

        this.toggle = this.toggle.bind(this);
    }

    toggle(){
        this.setState({visible: !this.state.visible});
    }

    render() {
        return (
            <div className={Strings.join(["card", this.props.shadow && "shadow", Bootstraps.mb(this.props.mb)])} >
                <a href="#collapseCardExample" className="d-block card-header py-3" data-toggle="collapse" role="button" aria-expanded="true" aria-controls="collapseCardExample" onClick={this.toggle}>
                    <h6 className={Strings.join(["m-0", "font-weight-bold", Strings.join(["text", this.props.type], "-")])}>
                        {this.props.title}
                    </h6>
                </a>
                {Reacts.display(this.state.visible,
                    <div className="collapse show" id="collapseCardExample">
                        <div className="card-body">
                            {this.props.children}
                        </div>
                    </div>
                )}
            </div>
        );
    }
}