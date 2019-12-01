Spectrometer spec;

int main(int argc, const char **argv)
{
    string experiment;
    string subject;
    double weight;

    if (argc < 4)
    {
        cout << "Usage: " << argv[0] << " experiment subject weight" << endl;
        exit(0);
    }

    experiment = argv[1];
    subject = argv[2];
    weight = atof(argv[3]);

    curl_global_init(CURL_GLOBAL_ALL);

    if (!spec.init())
    {
        cout << "Cannot initialize USB device!" << endl;
        return -1;
    }

    cout << "Subject weight: " << weight << endl;

    cout << "Put subject on spectrometer and press enter when ready: " << endl;
    getchar();
    Spectrum result;
    spec.scan(result);

    result.title = experiment + "-" + subject;

    string id = saveScan(result, experiment, subject, weight);
    cout << "Scan ID: " << id << endl;

    spec.deinit();

    curl_global_cleanup();

    return 0;
}
