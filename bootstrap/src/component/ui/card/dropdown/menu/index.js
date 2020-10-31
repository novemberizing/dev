import React from 'react';
import DropdownCardMenuHeader from './header';
import DropdownCardMenuItem from './item';
import DropdownCardMenuDivider from './divider';

export default class DropdownCardMenu extends React.Component {
    render(){
        return (
            <div className="dropdown-menu dropdown-menu-right shadow animated--fade-in show" aria-labelledby="dropdownMenuLink">
                {this.props.children}
            </div>
        );
    }
}

DropdownCardMenu.Header = DropdownCardMenuHeader;
DropdownCardMenu.Item = DropdownCardMenuItem;
DropdownCardMenu.Divider = DropdownCardMenuDivider;