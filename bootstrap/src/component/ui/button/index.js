import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React from 'react';
import Strings from '../../../util/strings';

export default class Button extends React.Component {
    render() {
        return (
            <a href={this.props.href} className={Strings.join(["btn", Strings.join(["btn", this.props.type]), this.props.circle && "btn-circle"])}>
                <FontAwesomeIcon icon={this.props.icon} />
            </a>
        );
    }
}