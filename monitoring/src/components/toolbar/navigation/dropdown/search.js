import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React from 'react';
import ToolbarNavDropdown from '.';

export default class ToolbarNavDropdownMenuSearch extends React.Component {
    render() {
        return (
            <ToolbarNavDropdown icon={["fas", "search"]} count={0} className={this.props.className}>
                <div className="dropdown-menu dropdown-menu-right p-3 shadow animated--grow-in" style={{display:"block"}}>
                    <form className="form-inline mr-auto w-100 navbar-search">
                        <div className="input-group">
                            <input type="text" className="form-control bg-light border-0 small" placeholder="Search for..." aria-label="Search" aria-describedby="basic-addon2" />
                            <div className="input-group-append">
                                <button className="btn btn-primary" type="button">
                                    <FontAwesomeIcon icon={["fas", "search"]} size="1x" />
                                </button>
                            </div>
                        </div>
                    </form>
                </div>
            </ToolbarNavDropdown>
        );
    }
}