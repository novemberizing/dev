import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React from 'react';
import Card from '..';
import Strings from '../../../../util/strings';

export default class DashboardCard extends React.Component {
    render() {
        return (
            <Card xl={this.props.xl} md={this.props.md} height={this.props.height} py={this.props.py} border={this.props.border} type={this.props.type}>
                <div className="row no-gutters align-items-center">
                    <div className="col mr-2">
                        <div className={Strings.join(["text-xs", "font-weight-bold", "text-uppercase", "mb-1", Strings.join(["text", this.props.type], "-")])}>{this.props.title}</div>
                        <div className="h5 mb-0 font-weight-bold text-gray-800">
                            {this.props.children}
                        </div>
                    </div>
                    <div className="col-auto">
                        <FontAwesomeIcon icon={this.props.icon} className="text-gray-300" size="2x" />
                    </div>
                </div>
            </Card>
        );
    }
}