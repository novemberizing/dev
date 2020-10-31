import React from 'react';

import Bootstraps from '../../../../../util/bootstraps';
import Strings from '../../../../../util/strings';
import Sidebar from '../../../sidebar';

export default class TopbarNavInboxItem extends React.Component {
    constructor(props){
        super(props);

        this.state = {
            truncate: Sidebar.status()
        };

        this.truncate = this.truncate.bind(this);

        Sidebar.on(this.truncate);
    }

    truncate(state) {
        this.setState({truncate: state.toggle});
    }

    componentWillUnmount() {
        Sidebar.off(this.truncate);
    }

    render() {
        return (
            <a className="dropdown-item d-flex align-items-center" href="#">
                <div className="dropdown-list-image mr-3">
                    <img className="rounded-circle" src={this.props.image} alt={this.props.alt} />
                    <div className={Strings.join(["status-indicator",Bootstraps.className("bg", this.props.status)])}></div>
                </div>
                <div className={this.props.bold ? "font-weight-bold" : ""}>
                    <div className={this.state.truncate ? "text-truncate" : "text-truncate-max"}>
                        {this.props.message}
                    </div>
                    <div className="small text-gray-500">
                        {this.props.from}
                        ·
                        {this.props.time}
                    </div>
                </div>
            </a>
        );
    }
}