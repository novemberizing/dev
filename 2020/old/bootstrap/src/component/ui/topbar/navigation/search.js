import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React from 'react';
import Reacts from '../../../../util/reacts';
import TopbarNavDropdown from './dropdown';

export default class TopbarNavSearch extends TopbarNavDropdown {

    constructor(props) {
        super(props);
    }


    render() {
        return (
            <li className="nav-item dropdown no-arrow d-sm-none">
                <a className="nav-link dropdown-toggle" href="#" onClick={this.toggle}>
                    <FontAwesomeIcon icon={["fas", "search"]} fixedWidth />
                </a>
                {Reacts.display(this.state.visible, 
                    <div className="dropdown-menu dropdown-menu-right p-3 shadow animated--grow-in show" aria-labelledby="searchDropdown">
                        <form className="form-inline mr-auto w-100 navbar-search">
                            <div className="input-group">
                                <input type="text" className="form-control bg-light border-0 small" placeholder="Search for..." aria-label="Search" aria-describedby="basic-addon2" />
                                <div className="input-group-append">
                                    <button className="btn btn-primary" type="button">
                                        <i className="fas fa-search fa-sm"></i>
                                    </button>
                                </div>
                            </div>
                        </form>
                    </div>
                )}
            </li>
        );
    }
}