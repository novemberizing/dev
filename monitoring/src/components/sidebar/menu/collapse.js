import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React from 'react';

export default class SidebarCollapseMenu extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            visible: false
        };

        this.show = this.show.bind(this);

        console.log(this.props.children);
    }

    show() {
        console.log('this show');
        this.setState({visible: true});
    }

    render() {
        const { visible } = this.state;

        return (
            <li className="nav-item">
                <a className="nav-link collapsed" href="#" onClick={this.show}>
                    { this.props.icon && <FontAwesomeIcon icon={this.props.icon} fixedWidth /> }
                    <span>{this.props.name}</span>
                </a>
                <div className="collapse">
                    <div className="bg-white py-2 collapse-inner rounded">
                        <h6 className="collapse-header">Custom Components:</h6>
                        {this.props.children}
                    </div>
                </div>
          </li>
        );
    }
}

SidebarCollapseMenu.Item = class extends React.Component {
    render() {
        return (
            <a className="collapse-item" href="buttons.html">Buttons</a>
        );
    }
}