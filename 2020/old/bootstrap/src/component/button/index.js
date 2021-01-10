import React from 'react';
import Strings from '../../util/strings';

export default class Button extends React.Component {
    static className(type, additional = [], outline = false, size = null, block = false, active = false) {
        const name = Strings.join(["btn", outline ? "outline" : null, type], "-");
        if(size) {
            if(additional) {
                additional.push(Strings.join(["btn", size], "-"));
            } else {
                additional = [Strings.join(["btn", size], "-")];
            }
        }
        if(block) {
            if(additional) {
                additional.push("btn-block");
            } else {
                additional = ["btn-block"];
            }
        }
        if(active) {
            if(additional) {
                additional.push("active");
            } else {
                additional = ["active"];
            }
        }
        return Strings.join(["btn", name, additional])
    }

    render() {
        return (<button type="button" className={Button.className(this.props.type, this.props.className, this.props.outline, this.props.size, this.props.block)} disabled={this.props.disabled}>{this.props.children}</button>);
    }
}