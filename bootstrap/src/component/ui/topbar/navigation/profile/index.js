import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React from 'react';
import Reacts from '../../../../../util/reacts';
import TopbarNavDropdown from '../dropdown';

export default class TopbarNavProfile extends TopbarNavDropdown {
    render() {
        return (
            <li className="nav-item dropdown no-arrow">
                <a className="nav-link dropdown-toggle" href="#" id="userDropdown" role="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false" onClick={this.toggle}>
                    <span className="mr-2 d-none d-lg-inline text-gray-600 small">{this.props.name}</span>
                    <img className="img-profile rounded-circle" src={this.props.image} />
                </a>
                {Reacts.display(this.state.visible,
                    <div className="dropdown-menu dropdown-menu-right shadow animated--grow-in show" aria-labelledby="userDropdown">
                        <a className="dropdown-item" href="#">
                            <FontAwesomeIcon icon={["fas", "user"]} fixedWidth size="sm" className="mr-2 text-gray-400" />
                            Profile
                        </a>
                        <a className="dropdown-item" href="#">
                            <FontAwesomeIcon icon={["fas", "cogs"]} fixedWidth size="sm" className="mr-2 text-gray-400" />
                            Settings
                        </a>
                        <a className="dropdown-item" href="#">
                            <FontAwesomeIcon icon={["fas", "list"]} fixedWidth size="sm" className="mr-2 text-gray-400" />
                            Activity Log
                        </a>
                        <div className="dropdown-divider"></div>
                        <a className="dropdown-item" href="#" data-toggle="modal" data-target="#logoutModal">
                            <FontAwesomeIcon icon={["fas", "sign-out-alt"]} fixedWidth size="sm" className="mr-2 text-gray-400" />
                            Logout
                        </a>
                    </div>
                )}
            </li>
        );
    }
}