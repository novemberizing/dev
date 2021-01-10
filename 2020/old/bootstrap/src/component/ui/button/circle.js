import Button from '.';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React from 'react';
import Strings from '../../../util/strings';


export default class CircleBtn extends Button {
    render() {
        return (
            <a href={this.props.href} className={Strings.join(["btn", Strings.join(["btn", this.props.type], "-"), "btn-circle", this.props.size ? `btn-${this.props.size}` : null])}>
                <FontAwesomeIcon icon={this.props.icon} />
            </a>
        );
    }
}