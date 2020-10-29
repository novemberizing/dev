import React from 'react';
import Strings from '../../util/strings';

export default class Alert extends React.Component {
    static className(type, additional = []) {
        const name = Strings.join(["alert", type], "-");
        return Strings.join(["alert", name, additional])
    }

    render() {
        const children = this.props.children && this.props.children.map(o => {
            console.log(o);
            if(o.type === 'a' && o.props) {
                o.props.className
                    = Strings.join([o.props.className, "alert-link"]);
            }
            return o;
        });
        return (
            <div className={Alert.className(this.props.type, this.props.className)} role="alert">
                {this.props.children}
            </div>
        );
    }
}