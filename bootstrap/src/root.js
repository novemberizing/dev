import React from 'react';
import Alert from './component/alert';
import Badge from './component/badge';
import Link from './component/basis/link';
import Breadcrumb from './component/breadcrumb';

export default class Root extends React.Component {
    render() {
        return (
            <div>
                <Alert type="primary">
                    PRIMARY
                    <Link href="#">Hello world</Link>
                    <div>
                        <a href="#">hello world</a>
                        <Link href="#" className="hello">Hello World</Link>
                    </div>
                    <a href="#">hello world</a>
                </Alert>
                <Alert type="secondary">SECONDARY</Alert>
                <Alert type="success">SUCCESS</Alert>
                <Alert type="danger">DANGER</Alert>
                <Alert type="warning">WARNING</Alert>
                <Alert type="info">INFO</Alert>
                <Alert type="light">LIGHT</Alert>
                <Alert type="dark">DARK</Alert>

                <Badge link={true} type="secondary" href="#">SECONDARY</Badge>
                <Badge link={true} type="success" href="#">SUCCESS</Badge>
                <Badge link={true} type="danger" href="#">DANGER</Badge>
                <Badge link={true} type="warning" href="#">WARNING</Badge>
                <Badge link={true} type="info" href="#">INFO</Badge>
                <Badge link={true} type="light" href="#">LIGHT</Badge>
                <Badge link={true} type="dark" href="#">DARK</Badge>

                <Badge type="secondary" href="#">SECONDARY</Badge>
                <Badge type="success" href="#">SUCCESS</Badge>
                <Badge type="danger" href="#">DANGER</Badge>
                <Badge type="warning" href="#">WARNING</Badge>
                <Badge type="info" href="#">INFO</Badge>
                <Badge type="light" href="#">LIGHT</Badge>
                <Badge type="dark" href="#">DARK</Badge>

                <Badge link={true} type="secondary" href="#" pill={true}>SECONDARY</Badge>
                <Badge link={true} type="success" href="#" pill={true}>SUCCESS</Badge>
                <Badge link={true} type="danger" href="#" pill={true}>DANGER</Badge>
                <Badge link={true} type="warning" href="#" pill={true}>WARNING</Badge>
                <Badge link={true} type="info" href="#" pill={true}>INFO</Badge>
                <Badge link={true} type="light" href="#" pill={true}>LIGHT</Badge>
                <Badge link={true} type="dark" href="#" pill={true}>DARK</Badge>

                <Badge type="secondary" href="#" pill={true}>SECONDARY</Badge>
                <Badge type="success" href="#" pill={true}>SUCCESS</Badge>
                <Badge type="danger" href="#" pill={true}>DANGER</Badge>
                <Badge type="warning" href="#" pill={true}>WARNING</Badge>
                <Badge type="info" href="#" pill={true}>INFO</Badge>
                <Badge type="light" href="#" pill={true}>LIGHT</Badge>
                <Badge type="dark" href="#" pill={true}>DARK</Badge>

                <Breadcrumb>
                    <Breadcrumb.Item active={true}>Home</Breadcrumb.Item>
                </Breadcrumb>
                <Breadcrumb>
                    <Breadcrumb.Item>Home</Breadcrumb.Item>
                    <Breadcrumb.Item active={true}>Library</Breadcrumb.Item>
                </Breadcrumb>
                <Breadcrumb>
                    <Breadcrumb.Item separator=":">Home</Breadcrumb.Item>
                    <Breadcrumb.Item separator=":">Library</Breadcrumb.Item>
                    <Breadcrumb.Item separator=":" active={true}>Data</Breadcrumb.Item>
                </Breadcrumb>
            </div>
        );
    }
}