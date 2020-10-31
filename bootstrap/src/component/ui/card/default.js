import React from 'react';
import Bootstraps from '../../../util/bootstraps';
import Reacts from '../../../util/reacts';
import Strings from '../../../util/strings';

export default class DafaultCard extends React.Component {
    render() {
        return (
            <div className={Strings.join(["card", Bootstraps.mb(this.props.mb)])} >
                {Reacts.display(this.props.title,
                    <div className="card-header">
                        {this.props.title}
                    </div>
                )}
                <div className="card-body">
                    {this.props.children}
                </div>
            </div>
        );
    }
}