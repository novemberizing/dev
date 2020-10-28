import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React from 'react';
import Strings from '../../util/string';

export default class ToolbarBtn extends React.Component {
    render() {
        const styles = ["btn", "btn-link", "rounded-circle", "mr-3"];
        return (
            <button className={Strings.concat([styles, this.props.className])}>
                { this.props.icon && <FontAwesomeIcon icon={this.props.icon} />}
            </button>
        );
    }
}