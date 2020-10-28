import React from 'react';
import ToolbarBtn from './button';
import ToolbarNav from './navigation';
import ToolbarSearch from './search';

export default class Toolbar extends React.Component {
    render() {
        return (
            <nav className="navbar navbar-expand navbar-light bg-white topbar mb-4 static-top shadow">
                {this.props.children}
            </nav>
        );
    }
}

Toolbar.Btn = ToolbarBtn;
Toolbar.Search = ToolbarSearch;
Toolbar.Nav = ToolbarNav;