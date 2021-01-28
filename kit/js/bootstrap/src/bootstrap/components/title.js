import React from 'react';
import Collections from '../../util/collections';
import Strings from '../../util/strings';

import Context from '../context';

export default class Title extends Context {
    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            children,
            size,
            ...additional
        } = this.props;

        const parent = Collections.last(this.context.type);

        const classNames = Strings.join([
            className,
            parent === 'card' && 'card-title',
            parent === 'modal' && 'modal-title'
        ]);

        const props = Object.assign(additional,
            {}
        );
        
        switch(size) {
            case 1:  return <h1 className={classNames} {...props}>{children}</h1>;
            case 2:  return <h2 className={classNames} {...props}>{children}</h2>;
            case 3:  return <h3 className={classNames} {...props}>{children}</h3>;
            case 4:  return <h4 className={classNames} {...props}>{children}</h4>;
            case 5:  return <h5 className={classNames} {...props}>{children}</h5>;
            case 6:  return <h6 className={classNames} {...props}>{children}</h6>;
            default: return <div className={classNames} {...props}>{children}</div>;
        }
    }
}