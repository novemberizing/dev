import React from 'react';
import Strings from '../../util/strings';
import Link from '../../component/basis/link';

export default class Alert extends React.Component {
    static className(type, additional = []) {
        const name = Strings.join(["alert", type], "-");
        return Strings.join(["alert", name, additional])
    }

    render() {
        const f = (children, func) => {
            return React.Children.map(children, (o) => {
                if(o instanceof Object) {
                    if(o.type === 'a' || o.type === Link) {
                        let props = {};
                        if(o.props.children) {
                            props.children = func(o.props.children, func);
                        }
                        props.className = Strings.join([o.props.className, "alert-link"]);
                        o = React.cloneElement(o, props);
                    } else {
                        if(o.props.children) {
                            let props = {};
                            props.children = func(o.props.children, func);
                            o = React.cloneElement(o, props);
                        }
                    }
                }
                return o;
            });
        };

        const children = f(this.props.children, f);

        return (
            <div className={Alert.className(this.props.type, this.props.className)} role="alert">
                {children}
            </div>
        );
    }
}