import React from 'react';
import Alert from './component/alert';
import Badge from './component/badge';
import Button from './component/button';
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

                <Button type="secondary">SECONDARY</Button>
                <Button type="success">SUCCESS</Button>
                <Button type="danger">DANGER</Button>
                <Button type="warning">WARNING</Button>
                <Button type="info">INFO</Button>
                <Button type="light">LIGHT</Button>
                <Button type="dark">DARK</Button>

                <Button type="secondary" className="text-nowrap">SECONDARY</Button>
                <Button type="success" className="text-nowrap">SUCCESS</Button>
                <Button type="danger" className="text-nowrap">DANGER</Button>
                <Button type="warning" className="text-nowrap">WARNING</Button>
                <Button type="info" className="text-nowrap">INFO</Button>
                <Button type="light" className="text-nowrap">LIGHT</Button>
                <Button type="dark" className="text-nowrap">DARK</Button>

                <Button type="secondary" outline={true}>SECONDARY</Button>
                <Button type="success" outline={true}>SUCCESS</Button>
                <Button type="danger" outline={true}>DANGER</Button>
                <Button type="warning" outline={true}>WARNING</Button>
                <Button type="info" outline={true}>INFO</Button>
                <Button type="light" outline={true}>LIGHT</Button>
                <Button type="dark" outline={true}>DARK</Button>

                <Button type="secondary" outline={true} size="sm">SECONDARY</Button>
                <Button type="success" outline={true} size="sm">SUCCESS</Button>
                <Button type="danger" outline={true} size="sm">DANGER</Button>
                <Button type="warning" outline={true} size="sm">WARNING</Button>
                <Button type="info" outline={true} size="sm">INFO</Button>
                <Button type="light" outline={true} size="sm">LIGHT</Button>
                <Button type="dark" outline={true} size="sm">DARK</Button>

                <Button type="secondary" outline={true} size="lg">SECONDARY</Button>
                <Button type="success" outline={true} size="lg">SUCCESS</Button>
                <Button type="danger" outline={true} size="lg">DANGER</Button>
                <Button type="warning" outline={true} size="lg">WARNING</Button>
                <Button type="info" outline={true} size="lg">INFO</Button>
                <Button type="light" outline={true} size="lg">LIGHT</Button>
                <Button type="dark" outline={true} size="lg">DARK</Button>

                <Button type="secondary" outline={true} size="lg" block={true}>SECONDARY</Button>
                <Button type="success" outline={true} size="lg" block={true}>SUCCESS</Button>
                <Button type="danger" outline={true} size="lg" block={true}>DANGER</Button>
                <Button type="warning" outline={true} size="lg" block={true}>WARNING</Button>
                <Button type="info" outline={true} size="lg" block={true}>INFO</Button>
                <Button type="light" outline={true} size="lg" block={true}>LIGHT</Button>
                <Button type="dark" outline={true} size="lg" block={true}>DARK</Button>

                <Button type="secondary" outline={true} size="lg" block={true} active={true}>SECONDARY</Button>
                <Button type="success" outline={true} size="lg" block={true} active={true}>SUCCESS</Button>
                <Button type="danger" outline={true} size="lg" block={true} active={true}>DANGER</Button>
                <Button type="warning" outline={true} size="lg" block={true} active={true}>WARNING</Button>
                <Button type="info" outline={true} size="lg" block={true} active={true}>INFO</Button>
                <Button type="light" outline={true} size="lg" block={true} active={true}>LIGHT</Button>
                <Button type="dark" outline={true} size="lg" block={true} active={true}>DARK</Button>

                <Button type="secondary" outline={true} size="lg" block={true} active={true} disabled={true}>SECONDARY</Button>
                <Button type="success" outline={true} size="lg" block={true} active={true} disabled={true}>SUCCESS</Button>
                <Button type="danger" outline={true} size="lg" block={true} active={true} disabled={true}>DANGER</Button>
                <Button type="warning" outline={true} size="lg" block={true} active={true} disabled={true}>WARNING</Button>
                <Button type="info" outline={true} size="lg" block={true} active={true} disabled={true}>INFO</Button>
                <Button type="light" outline={true} size="lg" block={true} active={true} disabled={true}>LIGHT</Button>
                <Button type="dark" outline={true} size="lg" block={true} active={true} disabled={true}>DARK</Button>
            </div>
        );
    }
}