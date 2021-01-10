import React from 'react';
import Strings from '../../../util/strings';

export default class SidebarDivider extends React.Component {
    render() {
        return (<hr className={Strings.join(["sidebar-divider", this.props.className])} />);
    }
}