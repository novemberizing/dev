import Button from '.';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React from 'react';
import Strings from '../../../util/strings';

export default class SplitBtn extends Button {
    render() {
        return (
            <a href={this.props.href} className={Strings.join(["btn", Strings.join(["btn", this.props.type], "-"), "btn-icon-split", this.props.size ? `btn-${this.props.size}` : null])}>
                <span className="icon text-white-50">
                    <FontAwesomeIcon icon={this.props.icon} />
                </span>
                <span className="text">
                    {this.props.children}
                </span>
            </a>
        );
    }
}
