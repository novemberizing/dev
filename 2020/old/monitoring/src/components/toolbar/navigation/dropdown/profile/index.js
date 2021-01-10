import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React from 'react';

export default class ToolbarNavDropdownProfile extends React.Component {
    render() {
        return (
            <li className="nav-item dropdown no-arrow">
                <a className="nav-link dropdown-toggle" href="#" id="userDropdown" role="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                    <span className="mr-2 d-none d-lg-inline text-gray-600 small">{this.props.name}</span>
                    <img className="img-profile rounded-circle" src={this.props.image} />
                </a>
                <div className="dropdown-menu dropdown-menu-right shadow animated--grow-in" aria-labelledby="userDropdown" style={{display:"block"}}>
                    <a className="dropdown-item" href="#">
                        <FontAwesomeIcon icon={["fas", "user"]} className="mr-2 text-gray-400" fixedWidth size="1x" />
                        Profile
                    </a>
                    <a className="dropdown-item" href="#">
                        <FontAwesomeIcon icon={["fas", "cogs"]} className="mr-2 text-gray-400" fixedWidth size="1x" />
                        Settings
                    </a>
                    <a className="dropdown-item" href="#">
                        <FontAwesomeIcon icon={["fas", "list"]} className="mr-2 text-gray-400" fixedWidth size="1x" />
                        Activity Log
                    </a>
                    <div className="dropdown-divider"></div>
                    <a className="dropdown-item" href="#">
                        <FontAwesomeIcon icon={["fas", "sign-out-alt"]} className="mr-2 text-gray-400" fixedWidth size="1x" />
                        Logout
                    </a>
                </div>
            </li>
        );
    }
}