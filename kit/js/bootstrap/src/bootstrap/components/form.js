import React from 'react';
import Collections from '../../util/collections';
import Strings from '../../util/strings';
import Context from '../context';

export default class Form extends Context {
    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            children,
            disabled,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            className
        ]);

        const props = Object.assign(additional,
            {}
        );
        const context = {
            type: Context.push(this.context.type, "form")
        };

        return (
            <Context.Provider value={context}>
                <form className={classNames} {...props}>
                    {disabled ? <fieldset disabled>{children}</fieldset> : children}
                </form>
            </Context.Provider>
        );
    }
}