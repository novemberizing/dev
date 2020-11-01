import Button from '.';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React from 'react';
import Strings from '../../../util/strings';


export default class BrandBtn extends Button {
    render() {
        return (
            <a href={this.props.href} className={Strings.join(["btn", "btn-block", Strings.join(["btn", this.props.brand], "-")])}>
                <FontAwesomeIcon icon={["fab", "google"]} fixedWidth /> {this.props.children}
            </a>
        );
    }
}