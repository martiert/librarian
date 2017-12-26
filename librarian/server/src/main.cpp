#include <simple-web-server/server_http.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/program_options.hpp>

#include <chrono>
#include <iostream>
#include <memory>
#include <sstream>
#include <thread>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <experimental/optional>

using namespace std::literals;
namespace po = boost::program_options;

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

struct Options {
    int threads;
    int port;
    std::string address;

    Options()
        : threads(1)
        , port(80)
    {}
};


Options read_properties(std::string const & filename)
{
    Options options;

    std::ifstream fs(filename);
    boost::property_tree::ptree ptree;
    boost::property_tree::read_json(fs, ptree);

    for (auto & property : ptree.get_child("")) {
        if (property.first == "threads")
            options.threads = std::stoi(property.second.data());
        if (property.first == "port")
            options.port = std::stoi(property.second.data());
        if (property.first == "address")
            options.address = property.second.data();
    }

    return options;
}


std::experimental::optional<Options> get_options(int argc, char ** argv)
{
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "Show this message")
            ("config", po::value<std::string>()->default_value("/etc/librarian/config.json"), "Path of configuration file")
            ("threads", po::value<int>(), "Number of threads in the thread pool")
            ("port", po::value<int>(), "Listening port")
            ("address", po::value<std::string>(), "Listening address")
            ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help") != 0) {
        std::cout << desc << std::endl;
        return std::experimental::nullopt;
    }

    auto options = read_properties(vm["config"].as<std::string>());

    if (vm.count("threads") == 1)
        options.threads = vm["threads"].as<int>();
    if (vm.count("port") == 1)
        options.port = vm["port"].as<int>();
    if (vm.count("address") == 1)
        options.address = vm["address"].as<std::string>();

    return options;
}


int main(int argc, char ** argv)
{
    HttpServer server;

    auto options = get_options(argc, argv);
    if (!options)
        return 0;

    server.config.thread_pool_size = options->threads;
    server.config.port = options->port;
    server.config.address = options->address;

    server.resource["^/info$"]["GET"] = [](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request) {
        response->write("Not delayed");
    };

    server.resource["^/delay$"]["GET"] = [](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request) {
        std::this_thread::sleep_for(10s);
        response->write("Delayed");
    };


    server.on_error = [](std::shared_ptr<HttpServer::Request>, const SimpleWeb::error_code & ec) {
        if (ec != SimpleWeb::asio::error::eof)
            std::cerr << "Some error happened: " << ec.value() << std::endl;
    };

    std::thread thread([&server]() {
        server.start();
    });

    thread.join();
}
