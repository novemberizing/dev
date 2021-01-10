import React from 'react';
import Strings from '../../../util/string';

export default class ToolbarNavItem extends React.Component {
    render() {
        const styles = ["nav-item", "dropdown", "no-arrow"];
        return (
            <li className={Strings.concat([styles, this.props.className])}>
                {this.props.children}
            </li>
        );
    }
}