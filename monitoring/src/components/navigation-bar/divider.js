import React from 'react';
import Strings from '../../util/string';

export default class NavigationBarDivider extends React.Component {
    render() {
        return (<hr className={Strings.concat(["sidebar-divider", this.props.className])}></hr>);
    }
}