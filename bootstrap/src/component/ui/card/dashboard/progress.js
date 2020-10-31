import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React from 'react';
import Card from '..';
import Strings from '../../../../util/strings';

export default class DashboardProgressCard extends React.Component {
    render() {
        return (
            <Card xl={this.props.xl} md={this.props.md} height={this.props.height} py={this.props.py} border={this.props.border} type={this.props.type}>
                <div className="row no-gutters align-items-center">
                    <div className="col mr-2">
                        <div className={Strings.join(["text-xs", "font-weight-bold", "text-uppercase", "mb-1", Strings.join(["text", this.props.type], "-")])}>{this.props.title}</div>

                        <div className="row no-gutters align-items-center">
                            <div className="col-auto">
                                <div className="h5 mb-0 mr-3 font-weight-bold text-gray-800">
                                    {this.props.children}
                                </div>
                            </div>
                            <div className="col">
                                <div className="progress progress-sm mr-2">
                                    <div className="progress-bar bg-info" role="progressbar" style={{width: "50%"}} aria-valuenow="50" aria-valuemin="0" aria-valuemax="100"></div>
                                </div>
                            </div>
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